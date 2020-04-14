//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#include "Lexeme.hpp"

#include <boost/format.hpp>

namespace clnt {
    Lexeme::Lexeme(clnt::SString const& source, clnt::LexemeType type, size_t i, size_t j): source(source), type(type), i(i), j(j) {}
    Lexeme::Lexeme(clnt::SString const& source, clnt::LexemeType type): source(source), type(type), i(0), j(source.size()) {}

    std::ostream& operator<<(std::ostream& out, Lexeme const& l) {
        return out << boost::format("(%s, %s)") % l.source % l.type;
    }

}