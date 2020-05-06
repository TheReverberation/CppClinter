//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#include "calphabet.hpp"

#include <iterator>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::copy;
using std::back_inserter;

namespace clnt::alphabet {

    vector<Slice<string>> UNARY_OPERATORS, OPERATORS;
    vector<Slice<string>> BINARY_OPERATORS, ACCESS_OPERATORS, RESERVED;

    void init() {
        vector<string> binary = {
                "+", "-", "*", "/", "^", "&", "|", "=", "~", "<", ">", "%", "+=", "-=", \
                    "*=", "/=", "^=", "&=", "|=", "==", "!=", "~=", "%=", ">=", "<=", "<<", ">>", \
                    "&&", "||"
        };
        for (auto& op : binary) {
            BINARY_OPERATORS.emplace_back(std::make_shared<string>(op));
        }

        vector<string> unary = {
               "++", "--", "*", "&", "!", "-"
        };

        for (auto& op : unary) {
           UNARY_OPERATORS.emplace_back(std::make_shared<string>(op));
        }

        vector<string> reserved = {
                "break", "for", "while", "struct", "class", "if", "else"
        };

        for (auto& op : reserved) {
            RESERVED.emplace_back(std::make_shared<string>(op));
        }

        vector<string> access = {
                "->", "."
        };

        for (auto& op : access) {
            ACCESS_OPERATORS.emplace_back(std::make_shared<string>(op));
        }

        copy(BINARY_OPERATORS.begin(), BINARY_OPERATORS.end(), back_inserter(OPERATORS));
        copy(UNARY_OPERATORS.begin(), UNARY_OPERATORS.end(), back_inserter(OPERATORS));
        copy(ACCESS_OPERATORS.begin(), ACCESS_OPERATORS.end(), back_inserter(OPERATORS));
    }
}
