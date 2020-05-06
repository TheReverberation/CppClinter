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

    shared_ptr<Lexeme> const
        LINE_BREAK = make_shared<Lexeme>(LexemeType::LINE_BREAK, make_shared<string>("\n")),
        QUESTION = make_shared<Lexeme>(LexemeType::QUESTION, make_shared<string>("?")),
        BACKSLASH = make_shared<Lexeme>(LexemeType::BACKSLASH, make_shared<string>("\\")),
        COMMA = make_shared<Lexeme>(LexemeType::COMMA, make_shared<string>(",")),
        COLON = make_shared<Lexeme>(LexemeType::COLON, make_shared<string>(":")),
        SEMICOLON = make_shared<Lexeme>(LexemeType::SEMICOLON, make_shared<string>(";"));
}
