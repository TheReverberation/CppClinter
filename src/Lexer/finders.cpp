//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#include <algorithm>
#include <memory>
#include "src/calphabet.hpp"


#include "finders.hpp"


using std::find;
using std::make_unique;
using std::pair;
using std::unique_ptr;
using std::string;
using std::make_pair;

namespace {
    pair<unique_ptr<clnt::lex::Lexeme>, size_t> NOTFOUND() { return {nullptr, 0}; }
}

namespace clnt::lex::finders {
    bool isident(char c) {
        return isdigit(c) || isalpha(c) || c == '_';
    }

    size_t findNonSpace(Slice<string> const& s, Vector<char> const& whitespaces) {
        size_t i = 0;
        for (i = 0; i < s.size() &&
            find(whitespaces.begin(), whitespaces.end(), s[i]) != whitespaces.end(); ++i);
        return i;
    }

    pair<unique_ptr<Lexeme>, size_t> findName(Slice<string> const& s) {
        if (!isident(s[0])) {
            return NOTFOUND();
        }
        size_t i = 0;
        for (; i < s.size() && isident(s[i]); ++i);
        return {make_unique<Lexeme>(LexemeType::NAME, s.slice(0, i)), i};
    }

    pair<unique_ptr<Lexeme>, size_t> findBackslash(Slice<string> const& s) {
        return s[0] == '\\' ? pair<unique_ptr
<Lexeme>, size_t>{make_unique<Lexeme>(LexemeType::BACKSLASH, s.slice(0, 1)), 1} : NOTFOUND();
    }


    pair<unique_ptr<Lexeme>, size_t> findOperator(Slice<string> const& s) {
        if (find(alphabet::operators().begin(), alphabet::operators().end(), s.slice(0, 2)) != alphabet::operators().end()) {
            return {make_unique<Lexeme>(LexemeType::OPERATOR, s.slice(0, 2)), 2};
        }
        if (find(alphabet::operators().begin(), alphabet::operators().end(), s.slice(0, 1)) != alphabet::operators().end()) {
            return {make_unique<Lexeme>(LexemeType::OPERATOR, s.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Lexeme>, size_t> findString(Slice<string> const& s) {
        if (s[0] != '\'' && s[0] != '\"') {
            return NOTFOUND();
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
            throw std::string("Incorrect str(endless)");
        }
    }

    pair<unique_ptr<Lexeme>, size_t> findNumber(Slice<string> const& s) {
        return NOTFOUND();
    }

    pair<unique_ptr<Lexeme>, size_t> findConstant(Slice<string> const& s) {
        return findString(s);
    }

    pair<unique_ptr<Lexeme>, size_t> findColon(Slice<string> const& s) {
        return s[0] == ':' ? pair<unique_ptr
<Lexeme>, size_t>{make_unique<Lexeme>(LexemeType::COLON, s.slice(0, 1)), 1} : NOTFOUND();
    }

    pair<unique_ptr<Lexeme>, size_t> findSemicolon(Slice<string> const& s) {
        return s[0] == ';' ? pair<unique_ptr
<Lexeme>, size_t>{make_unique<Lexeme>(LexemeType::SEMICOLON, s.slice(0, 1)), 1} : NOTFOUND();
    }


    pair<unique_ptr<Lexeme>, size_t> findComma(Slice<string> const& s) {
        return s[0] == ',' ? pair<unique_ptr
<Lexeme>, size_t>{make_unique<Lexeme>(LexemeType::COMMA, s.slice(0, 1)), 1} : NOTFOUND();
    }


    pair<unique_ptr<Lexeme>, size_t> findLinebreak(Slice<string> const& s) {
        return s[0] == '\n' ? pair<unique_ptr
<Lexeme>, size_t>{make_unique<Lexeme>(LexemeType::LINE_BREAK, s.slice(0, 1)), 1}: NOTFOUND();
    }


    pair<unique_ptr<Lexeme>, size_t> findQuestion(Slice<string> const& s) {
        return s[0] == '?' ? pair<unique_ptr
<Lexeme>, size_t>{make_unique<Lexeme>(LexemeType::QUESTION, s.slice(0, 1)), 1} : NOTFOUND();
    }


    pair<unique_ptr<Lexeme>, size_t> findOpenBracket(Slice<string> const& s) {
        return (s[0] == '(' || s[0] == '[' || s[0] == '{') ?
               pair<unique_ptr
        <Lexeme>, size_t>(make_unique<Lexeme>(LexemeType::OPEN_BRACKET, s.slice(0, 1)), 1) : NOTFOUND();
    }

    pair<unique_ptr<Lexeme>, size_t> findCloseBracket(Slice<string> const& s) {
        return (s[0] == ')' || s[0] == ']' || s[0] == '}') ?
               pair<unique_ptr
        <Lexeme>, size_t>(make_unique<Lexeme>(LexemeType::CLOSE_BRACKET, s.slice(0, 1)), 1) : NOTFOUND();
    }

    std::pair<std::unique_ptr<Lexeme>, size_t> findSharp(Slice<std::string> const& s) {
        return s[0] == '#' ? pair<unique_ptr
<Lexeme>, size_t>{make_unique<Lexeme>(LexemeType::SHARP, s.slice(0, 1)), 1} : NOTFOUND();
    }

    Vector<LexemeFinder> FINDERS;

    void init() {
        FINDERS = {
            findName, findBackslash, findOperator, findConstant,
            findColon, findSemicolon, findQuestion, findLinebreak, findComma,
            findOpenBracket, findCloseBracket, findSharp,
        };
        std::cout << "Finders\n";
        std::cout << FINDERS.size() << '\n';
        for (auto& now : FINDERS) {
            std::cout << (void*)now << '\n';
        }
    }

}
