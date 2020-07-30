//
// Created by Daniil Nedaiborsch on 16.04.2020.
//

#include "Statement.hpp"

namespace clnt::states {

    Statement::Statement(StatementType type, Slice<vector<Token*>> tokens): type(type), tokens(std::move(tokens)) {}

    Statement::~Statement() {
        std::cout << "Statement: " << type << " destructed\n";
    }

    void Statement::lint() const {
        throw err::UndefinedLinterError();
    }


    mem::PrimeGC<Statement> Statement::gc;

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
