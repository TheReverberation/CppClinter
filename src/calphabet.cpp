#include "calphabet.hpp"

#include <iterator>
#include <vector>
#include <string>
#include <memory>

using std::string;
using std::vector;
using std::copy;
using std::back_inserter;
using std::make_shared;

namespace clnt::alphabet {

    vector<Slice<string>> _UNARY_OPERATORS, _OPERATORS;
    vector<Slice<string>> _BINARY_OPERATORS, _ACCESS_OPERATORS, _RESERVED;

    void init() {
        vector<string> binary = {
                "+", "-", "*", "/", "^", "&", "|", "=", "~", "<", ">", "%", "+=", "-=", \
                "*=", "/=", "^=", "&=", "|=", "==", "!=", "~=", "%=", ">=", "<=", "<<", ">>", \
                "&&", "||"
        };
        for (auto& op : binary) {
            _BINARY_OPERATORS.emplace_back(make_shared<string>(op));
        }
        vector<string> unary = {
               "++", "--", "*", "&", "!", "-"
        };
        for (auto& op : unary) {
           _UNARY_OPERATORS.emplace_back(make_shared<string>(op));
        }

        vector<string> reserved = {
                "break", "for", "while", "struct", "class", "if", "else", "case", "switch", "typedef",
        };

        for (auto& op : reserved) {
            _RESERVED.emplace_back(make_shared<string>(op));
        }

        vector<string> access = {
                "->", "."
        };

        for (auto& op : access) {
            _ACCESS_OPERATORS.emplace_back(make_shared<string>(op));
        }

        copy(_BINARY_OPERATORS.begin(), _BINARY_OPERATORS.end(), back_inserter(_OPERATORS));
        copy(_UNARY_OPERATORS.begin(), _UNARY_OPERATORS.end(), back_inserter(_OPERATORS));
        copy(_ACCESS_OPERATORS.begin(), _ACCESS_OPERATORS.end(), back_inserter(_OPERATORS));
    }

    std::vector<Slice<std::string>> const& accessOperators() {
        return _ACCESS_OPERATORS;
    }

    std::vector<Slice<std::string>> const& callOperators() {
        return {};
    }

    std::vector<Slice<std::string>> const& unaryOperators() {
        return _UNARY_OPERATORS;
    }

    std::vector<Slice<std::string>> const& operators() {
        return _OPERATORS;
    }

    std::vector<Slice<std::string>> const& commaOperator() {
        return {};
    }

    std::vector<Slice<std::string>> const& binaryOperators() {
        return _BINARY_OPERATORS;
    }

    std::vector<Slice<std::string>> const& reserved() {
        return _RESERVED;
    }
}
