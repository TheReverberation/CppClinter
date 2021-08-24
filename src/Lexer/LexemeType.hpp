/*
 * It represents all lexeme types
 */

#pragma once

#include <iostream>
#include <string>

namespace clnt::lex {

    enum struct LexemeType: uint8_t {
        NAME, OPERATOR, OPEN_BRACKET, CLOSE_BRACKET, LINE_BREAK, QUESTION, CONSTANT,
        BACKSLASH, COMMA, UNDEFINED, COLON, SEMICOLON, SHARP, COMMENT
    };

    std::string getLexemeTypeName(LexemeType type);

    std::ostream& operator<<(std::ostream& out, LexemeType type);
    void initTypeNames();
}
