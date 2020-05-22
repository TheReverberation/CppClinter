//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#include <algorithm>
#include <memory>
#include "src/calphabet.hpp"


#include "finders.hpp"


using std::find;
using std::make_shared;
using std::pair;
using std::vector;
using std::shared_ptr;
using std::string;
using std::make_pair;

namespace {
    pair<shared_ptr<clnt::lex::Lexeme>, size_t> NOTFOUND = {nullptr, 0};
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

    pair<shared_ptr<Lexeme>, size_t> findName(Slice<string> const& s) {
        if (!isident(s[0])) {
            return NOTFOUND;
        }
        size_t i = 0;
        for (; i < s.size() && isident(s[i]); ++i);
        return {make_shared<Lexeme>(LexemeType::NAME, s.slice(0, i)), i};
    }

    pair<shared_ptr<Lexeme>, size_t> findBackslash(Slice<string> const& s) {
        return s[0] == '\\' ? pair<shared_ptr<Lexeme>, size_t>{make_shared<Lexeme>(LexemeType::BACKSLASH, s.slice(0, 1)), 1} : NOTFOUND;
    }


    pair<shared_ptr<Lexeme>, size_t> findOperator(Slice<string> const& s) {
        if (find(alphabet::operators().begin(), alphabet::operators().end(), s.slice(0, 2)) != alphabet::operators().end()) {
            return {make_shared<Lexeme>(LexemeType::OPERATOR, s.slice(0, 2)), 2};
        }
        if (find(alphabet::operators().begin(), alphabet::operators().end(), s.slice(0, 1)) != alphabet::operators().end()) {
            return {make_shared<Lexeme>(LexemeType::OPERATOR, s.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<shared_ptr<Lexeme>, size_t> findString(Slice<string> const& s) {
        if (s[0] != '\'' && s[0] != '\"') {
            return NOTFOUND;
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
            return {make_shared<Lexeme>(LexemeType::CONSTANT, s.slice(0, i)), i};
        } else {
            throw std::string("Incorrect str(endless)");
        }
    }

    pair<shared_ptr<Lexeme>, size_t> findNumber(Slice<string> const& s) {
        return NOTFOUND;
    }

    pair<shared_ptr<Lexeme>, size_t> findConstant(Slice<string> const& s) {
        return findString(s);
    }

    pair<shared_ptr<Lexeme>, size_t> findColon(Slice<string> const& s) {
        return s[0] == ':' ? pair<shared_ptr<Lexeme>, size_t>{make_shared<Lexeme>(LexemeType::COLON, s.slice(0, 1)), 1} : NOTFOUND;
    }

    pair<shared_ptr<Lexeme>, size_t> findSemicolon(Slice<string> const& s) {
        return s[0] == ';' ? pair<shared_ptr<Lexeme>, size_t>{make_shared<Lexeme>(LexemeType::SEMICOLON, s.slice(0, 1)), 1} : NOTFOUND;
    }


    pair<shared_ptr<Lexeme>, size_t> findComma(Slice<string> const& s) {
        return s[0] == ',' ? pair<shared_ptr<Lexeme>, size_t>{make_shared<Lexeme>(LexemeType::COMMA, s.slice(0, 1)), 1} : NOTFOUND;
    }


    pair<shared_ptr<Lexeme>, size_t> findLinebreak(Slice<string> const& s) {
        return s[0] == '\n' ? pair<shared_ptr<Lexeme>, size_t>{make_shared<Lexeme>(LexemeType::LINE_BREAK, s.slice(0, 1)), 1}: NOTFOUND;
    }


    pair<shared_ptr<Lexeme>, size_t> findQuestion(Slice<string> const& s) {
        return s[0] == '?' ? pair<shared_ptr<Lexeme>, size_t>{make_shared<Lexeme>(LexemeType::QUESTION, s.slice(0, 1)), 1} : NOTFOUND;
    }


    pair<shared_ptr<Lexeme>, size_t> findOpenBracket(Slice<string> const& s) {
        return (s[0] == '(' || s[0] == '[' || s[0] == '{') ?
               pair<shared_ptr<Lexeme>, size_t>(make_shared<Lexeme>(LexemeType::OPEN_BRACKET, s.slice(0, 1)), 1) : NOTFOUND;
    }

    pair<shared_ptr<Lexeme>, size_t> findCloseBracket(Slice<string> const& s) {
        return (s[0] == ')' || s[0] == ']' || s[0] == '}') ?
               pair<shared_ptr<Lexeme>, size_t>(make_shared<Lexeme>(LexemeType::CLOSE_BRACKET, s.slice(0, 1)), 1) : NOTFOUND;
    }

    std::pair<std::shared_ptr<Lexeme>, size_t> findSharp(Slice<std::string> const& s) {
        return s[0] == '#' ? pair<shared_ptr<Lexeme>, size_t>{make_shared<Lexeme>(LexemeType::SHARP, s.slice(0, 1)), 1} : NOTFOUND;
    }

    vector<LexemeFinder> FINDERS;

    void init() {
        FINDERS = {
            findName, findBackslash, findOperator, findConstant,
            findColon, findSemicolon, findQuestion, findLinebreak, findComma,
            findOpenBracket, findCloseBracket, findSharp,
        };
    }

}
