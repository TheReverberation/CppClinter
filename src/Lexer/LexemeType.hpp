#pragma once

#include <iostream>


namespace clnt::lex {

    enum struct LexemeType: uint8_t {
        NAME, OPERATOR, OPEN_BRACKET, CLOSE_BRACKET, LINE_BREAK, QUESTION, CONSTANT,
        BACKSLASH, COMMA, UNDEFINED, COLON, SEMICOLON, SHARP
    };

    std::ostream& operator<<(std::ostream& out, LexemeType type);
    void initTypeNames();
}
