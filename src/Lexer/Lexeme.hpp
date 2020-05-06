//
// Created by Daniil Nedaiborsch on 28.04.2020.
//

#pragma once


#include <string>
#include <memory>

#include <src/Slice.hpp>


#include "LexemeType.hpp"


namespace clnt::lex {
    class Lexeme {
    public:
        Lexeme(Lexeme const&) = delete;
        Lexeme(Lexeme&&) = delete;
        Lexeme(LexemeType type, Slice<std::string>);
        Slice<std::string> const source;
        LexemeType const type;
    };

    std::ostream& operator<<(std::ostream& out, Lexeme const& l);

    extern std::shared_ptr<Lexeme> const LINE_BREAK, QUESTION, BACKSLASH, COMMA, COLON, SEMICOLON;

}



