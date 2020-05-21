#include "TokenType.hpp"

namespace clnt::eval {

    std::string TYPE_NAMES[255];

    void initTypeNames() {
        for (size_t i = 0; i < 255; ++i) {
            TYPE_NAMES[i] = "${TypeName}";
        }

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
        TYPE_NAMES[(int)TokenType::UNDEFINED] = "Undefined";
    }

    std::ostream& operator<<(std::ostream& out, TokenType type) {
        return out << TYPE_NAMES[(int)type];
    }
}