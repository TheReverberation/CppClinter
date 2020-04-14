//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#include "CAlphabet.hpp"

#include <iterator>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::copy;
using std::back_inserter;

namespace clnt::alphabet {

    vector<SString> UNARY_OPERATORS, BINARY_OPERATORS, OPERATORS;

    void init() {
        vector<string> binary = {
                "+", "-", "*", "/", "^", "&", "|", "=", "~", "<", ">", "%", "+=", "-=", \
                    "*=", "/=", "^=", "&=", "|=", "==", "!=", "~=", "%=", ">=", "<=", "<<", ">>", \
                    "&&", "||"
        };
        for (auto& op : binary) {
            BINARY_OPERATORS.emplace_back(shared_ptr<string>(new string(op)));
        }

        vector<string> unary = {
               "++", "--", "*", "&", "!", "-"
        };

        for (auto& op : unary) {
           UNARY_OPERATORS.emplace_back(shared_ptr<string>(new string(op)));
        }

        copy(BINARY_OPERATORS.begin(), BINARY_OPERATORS.end(), back_inserter(OPERATORS));
        copy(UNARY_OPERATORS.begin(), UNARY_OPERATORS.end(), back_inserter(OPERATORS));
    }
}