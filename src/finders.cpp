//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#include <algorithm>
#include <cstring>
#include <memory>

#include "finders.hpp"
#include "CAlphabet.hpp"

using std::find;
using std::make_shared;

namespace clnt::finders {
    bool isident(char c) {
        return isdigit(c) || isalpha(c) || c == '_';
    }

    size_t findNonSpace(SString const& s, vector<char> const& whitespaces) {
        size_t i = 0;
        for (i = 0; i < s.size() &&
            find(whitespaces.begin(), whitespaces.end(), s[i]) != whitespaces.end(); ++i);
        return i;
    }

    shared_ptr<Lexeme> findName(SString const& s, shared_ptr<Lexeme> last) {
        if (!isident(s[0])) {
            return nullptr;
        }

        size_t i = 0;
        for (; i < s.size() && isident(s[i]); ++i);
        return make_shared<Lexeme>(s.slice(0, i), LexemeType::NAME);
    }

    shared_ptr<Lexeme> findBackslash(SString const& s, shared_ptr<Lexeme> last) {
        return s[0] == '\\' ? shared_ptr<Lexeme>(new Lexeme(s.slice(0, 1), LexemeType::BACKSLASH, 0, 1)) : nullptr;
    }


    shared_ptr<Lexeme> findOperator(SString const& s, shared_ptr<Lexeme> last) {
        if (find(alphabet::OPERATORS.begin(), alphabet::OPERATORS.end(), s.slice(0, 2)) != alphabet::OPERATORS.end()) {
            return shared_ptr<Lexeme>(new Lexeme(s.slice(0, 2), LexemeType::OPERATOR, 0, 2));
        }
        if (find(alphabet::OPERATORS.begin(), alphabet::OPERATORS.end(), s.slice(0, 1)) != alphabet::OPERATORS.end()) {
            return shared_ptr<Lexeme>(new Lexeme(s.slice(0, 1), LexemeType::OPERATOR, 0, 1));
        }
        return nullptr;
    }

    vector<Finder> finders;

    void init() {
        finders = {
                findName, findBackslash, findOperator
        };
    }

}
