//
// Created by Daniil Nedaiborsch on 16.04.2020.
//

#include "Statement.hpp"

using std::vector;
using std::move;
using std::string;

using clnt::eval::Tokens;

namespace clnt::states {

    Statement::Statement(StatementType type, Slice<Tokens> tokens): type(type), tokens(move(tokens)) {}


    void Statement::lint() const {
        throw err::UndefinedLinterError();
    }

    string const& Statement::linted() const {
        return _linted;
    }

    std::ostream& operator<<(std::ostream& out, Statement const& s) {
        out << "<" << s.type << ", [";
        for (size_t i = 0; i < s.tokens.size() - 1; ++i) {
            out << *s.tokens[i] << ", ";
        }
        return out << *s.tokens.back() << "]>";
    }
}
