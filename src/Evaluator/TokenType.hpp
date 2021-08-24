/*
 * Token types.
 */

#pragma once

#include <cstdint>
#include <iostream>
#include <string>


namespace clnt::eval {
    enum class TokenType: uint8_t {
        IDENTIFIER, RESERVED, BLOCK, BINARY_OPERATOR, UNARY_OPERATOR, ACCESS_OPERATOR, CALL_OPERATOR, UNDEFINED,
        SEMICOLON, LINE_BREAK, COMMA, SHARP, BACKSLASH, COLON, QUESTION, INITIALIZER, COMMENT
    };

    void initTypeNames();
    std::string tokenTypeName(TokenType type);
    std::ostream& operator<<(std::ostream& out, TokenType type);
}


