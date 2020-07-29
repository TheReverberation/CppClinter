#include "calphabet.hpp"

#include <iterator>
#include <string>
#include <memory>

#include <src/types.hpp>

using std::string;
using std::copy;
using std::back_inserter;
using std::make_shared;

namespace clnt::alphabet {

    Vector<Slice<string>> _UNARY_OPERATORS, _OPERATORS;
    Vector<Slice<string>> _BINARY_OPERATORS, _ACCESS_OPERATORS, _RESERVED;

    void init() {
        Vector<string> binary = {
                "+", "-", "*", "/", "^", "&", "|", "=", "~", "<", ">", "%", "+=", "-=", \
                "*=", "/=", "^=", "&=", "|=", "==", "!=", "~=", "%=", ">=", "<=", "<<", ">>", \
                "&&", "||"
        };
        for (auto& op : binary) {
            _BINARY_OPERATORS.push_back(make_shared<string>(op));
        }
        Vector<string> unary = {
               "++", "--", "*", "&", "!", "-"
        };
        for (auto& op : unary) {
           _UNARY_OPERATORS.push_back(make_shared<string>(op));
        }

        Vector<string> reserved = {
                "break", "for", "while", "struct", "class", "if", "else", "case", "switch", "typedef",
        };

        for (auto& op : reserved) {
            _RESERVED.push_back(make_shared<string>(op));
        }

        Vector<string> access = {
                "->", "."
        };

        for (auto& op : access) {
            _ACCESS_OPERATORS.push_back(make_shared<string>(op));
        }

        copy(_BINARY_OPERATORS.begin(), _BINARY_OPERATORS.end(), back_inserter(_OPERATORS));
        copy(_UNARY_OPERATORS.begin(), _UNARY_OPERATORS.end(), back_inserter(_OPERATORS));
        copy(_ACCESS_OPERATORS.begin(), _ACCESS_OPERATORS.end(), back_inserter(_OPERATORS));
    }

    Vector<Slice<std::string>> const& accessOperators() {
        return _ACCESS_OPERATORS;
    }

    Vector<Slice<std::string>> const& callOperators() {
        return {};
    }

    Vector<Slice<std::string>> const& unaryOperators() {
        return _UNARY_OPERATORS;
    }

    Vector<Slice<std::string>> const& operators() {
        return _OPERATORS;
    }

    Vector<Slice<std::string>> const& commaOperator() {
        return {};
    }

    Vector<Slice<std::string>> const& binaryOperators() {
        return _BINARY_OPERATORS;
    }

    Vector<Slice<std::string>> const& reserved() {
        return _RESERVED;
    }
}
