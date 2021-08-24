#include <algorithm>
#include <memory>

#include <src/calphabet.hpp>

#include "finders.hpp"


using std::find;
using std::make_unique;
using std::pair;
using std::vector;
using std::unique_ptr;
using std::string;
using std::make_pair;

using clnt::util::Slice;
using clnt::util::makeSlice;

namespace {
    clnt::lex::finders::FoundLexeme notfound() { return {nullptr, 0}; }
}

namespace clnt::lex::finders {
    bool isident(char c) {
        return isdigit(c) || isalpha(c) || c == '_';
    }

    size_t findNonSpace(Slice<string> const& s, vector<char> const& whitespaces) {
        size_t i = 0;
        for (i = 0; i < s.size() &&
            find(whitespaces.begin(), whitespaces.end(), s[i]) != whitespaces.end(); ++i);
        return i;
    }

    FoundLexeme findName(Slice<string> const& s) {
        if (!isident(s[0])) {
            return notfound();
        }
        size_t i = 0;
        for (; i < s.size() && isident(s[i]); ++i);
        return {make_unique<Lexeme>(LexemeType::NAME, s.slice(0, i)), i};
    }

    FoundLexeme findBackslash(Slice<string> const& s) {
        return s[0] == '\\' ? FoundLexeme{make_unique<Lexeme>(LexemeType::BACKSLASH, s.slice(0, 1)), 1} : notfound();
    }


    FoundLexeme findOperator(Slice<string> const& s) {
        if (find(alphabet::operators().begin(), alphabet::operators().end(), s.slice(0, 2)) != alphabet::operators().end()) {
            return {make_unique<Lexeme>(LexemeType::OPERATOR, s.slice(0, 2)), 2};
        }
        if (find(alphabet::operators().begin(), alphabet::operators().end(), s.slice(0, 1)) != alphabet::operators().end()) {
            return {make_unique<Lexeme>(LexemeType::OPERATOR, s.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundLexeme findString(Slice<string> const& s) {
        if (s[0] != '\'' && s[0] != '\"') {
            return notfound();
        }
        char quote = s[0];
        size_t i = 1;
        bool hasEnd = false;
        while (i < s.size() && !hasEnd) {
            if (s[i] == '\\') {
                i += 2;
            } else {
                if (s[i] == quote) {
                    hasEnd = true;
                }
                ++i;
            }
        }
        if (hasEnd) {
            return {make_unique<Lexeme>(LexemeType::CONSTANT, s.slice(0, i)), i};
        } else {
            throw std::invalid_argument("Endless string");
        }
    }

    FoundLexeme findSingleLineComment(Slice<string> const& s) {
        if (s.slice(0, 2) == string("//")) {
            size_t i = 0;
            while (i < s.size() && s[i] != '\n') {
                ++i;
            }
            ++i;
            return {make_unique<Lexeme>(LexemeType::COMMENT, s.slice(0, i)), i};
        }
        return ::notfound();
    }

    FoundLexeme findMultiComment(Slice<string> const& s) {
        if (s.slice(0, 2) == string("/*")) {
            size_t i = 2;
            while (i < s.size() && s.slice(i - 2, i) != string("*/")) {
                ++i;
            }
            return {make_unique<Lexeme>(LexemeType::COMMENT, s.slice(0, i)), i};
        }
        return notfound();
    }

    FoundLexeme findComment(Slice<string> const& s) {
        auto found = findSingleLineComment(s);
        if (found.first) {
            return found;
        }
        found = findMultiComment(s);
        if (found.first) {
            return found;
        }
        return notfound();
    }

    FoundLexeme findNumber(Slice<string> const& s) {
        return notfound();
    }

    FoundLexeme findConstant(Slice<string> const& s) {
        return findString(s);
    }

    FoundLexeme findColon(Slice<string> const& s) {
        return s[0] == ':' ? FoundLexeme{make_unique<Lexeme>(LexemeType::COLON, s.slice(0, 1)), 1} : notfound();
    }

    FoundLexeme findSemicolon(Slice<string> const& s) {
        return s[0] == ';' ? FoundLexeme{make_unique<Lexeme>(LexemeType::SEMICOLON, s.slice(0, 1)), 1} : notfound();
    }


    FoundLexeme findComma(Slice<string> const& s) {
        return s[0] == ',' ? FoundLexeme{make_unique<Lexeme>(LexemeType::COMMA, s.slice(0, 1)), 1} : notfound();
    }


    FoundLexeme findLinebreak(Slice<string> const& s) {
        return s[0] == '\n' ? FoundLexeme{make_unique<Lexeme>(LexemeType::LINE_BREAK, s.slice(0, 1)), 1}: notfound();
    }


    FoundLexeme findQuestion(Slice<string> const& s) {
        return s[0] == '?' ? FoundLexeme{make_unique<Lexeme>(LexemeType::QUESTION, s.slice(0, 1)), 1} : notfound();
    }


    FoundLexeme findOpenBracket(Slice<string> const& s) {
        return (s[0] == '(' || s[0] == '[' || s[0] == '{') ?
               FoundLexeme(make_unique<Lexeme>(LexemeType::OPEN_BRACKET, s.slice(0, 1)), 1) : notfound();
    }

    FoundLexeme findCloseBracket(Slice<string> const& s) {
        return (s[0] == ')' || s[0] == ']' || s[0] == '}') ?
               FoundLexeme(make_unique<Lexeme>(LexemeType::CLOSE_BRACKET, s.slice(0, 1)), 1) : notfound();
    }

    FoundLexeme findSharp(Slice<std::string> const& s) {
        return s[0] == '#' ? FoundLexeme{make_unique<Lexeme>(LexemeType::SHARP, s.slice(0, 1)), 1} : notfound();
    }

    vector<LexemeFinder> FINDERS;

    void init() {
        FINDERS = {
            findComment, findName, findBackslash, findOperator, findConstant,
            findColon, findSemicolon, findQuestion, findLinebreak, findComma,
            findOpenBracket, findCloseBracket, findSharp,
        };
    }
}
