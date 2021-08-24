#include <algorithm>
#include <array>

#include "TokenType.hpp"

namespace {
    std::array<std::string, 255> TYPE_NAMES;
}

namespace clnt::eval {


    void initTypeNames() {
        std::fill(TYPE_NAMES.begin(), TYPE_NAMES.end(), "$(LexemeTypeName)$");

        TYPE_NAMES[(int)TokenType::BLOCK] = "Block";
        TYPE_NAMES[(int)TokenType::BINARY_OPERATOR] = "Binary";
        TYPE_NAMES[(int)TokenType::UNARY_OPERATOR] = "Unary";
        TYPE_NAMES[(int)TokenType::ACCESS_OPERATOR] = "Access";
        TYPE_NAMES[(int)TokenType::IDENTIFIER] = "Identifier";
        TYPE_NAMES[(int)TokenType::RESERVED] = "ReservedWord";
        TYPE_NAMES[(int)TokenType::CALL_OPERATOR] = "Call";
        TYPE_NAMES[(int)TokenType::UNDEFINED] = "Undefined";
        TYPE_NAMES[(int)TokenType::SEMICOLON] = "Semicolon";
        TYPE_NAMES[(int)TokenType::COMMA] = "Comma";
        TYPE_NAMES[(int)TokenType::LINE_BREAK] = "Linebreak";
        TYPE_NAMES[(int)TokenType::SHARP] = "Sharp";
        TYPE_NAMES[(int)TokenType::BACKSLASH] = "Backslash";
        TYPE_NAMES[(int)TokenType::COLON] = "Colon";
        TYPE_NAMES[(int)TokenType::UNDEFINED] = "Undefined";
        TYPE_NAMES[(int)TokenType::QUESTION] = "Question";
        TYPE_NAMES[(int)TokenType::INITIALIZER] = "Init";
        TYPE_NAMES[(int)TokenType::COMMENT] = "Comment";
    }

    std::string tokenTypeName(TokenType type) {
        return TYPE_NAMES[(int)type];
    }

    std::ostream& operator<<(std::ostream& out, TokenType type) {
        return out << tokenTypeName(type);
    }
}
