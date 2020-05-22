//
// Created by Daniil Nedaiborsch on 28.04.2020.
//

#include "Lexeme.hpp"

using std::string;
using std::make_shared;

namespace clnt::lex {
    Lexeme::Lexeme(LexemeType type, Slice<string> source): type(type), source(source) {}

    std::ostream& operator<<(std::ostream& out, Lexeme const& l) {
        out << "(" << l.type << ", "; 
        if (l.type == LexemeType::LINE_BREAK) {
            out << "\\n";
        } else {
            out << l.source;
        }
        return out << ")";
    }
}
