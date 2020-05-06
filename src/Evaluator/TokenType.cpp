//
// Created by Daniil Nedaiborsch on 19.04.2020.
//

#include "TokenType.hpp"

namespace clnt::eval {

    std::string TYPE_NAMES[255];

    void initTypeNames() {
        for (size_t i = 0; i < 255; ++i) {
            TYPE_NAMES[i] = "${TypeName}";
        }

        TYPE_NAMES[(int)TokenType::BLOCK] = "Block";
        TYPE_NAMES[(int)TokenType::BINARY_OPERATOR] = "BinaryOperator";
        TYPE_NAMES[(int)TokenType::UNARY_OPERATOR] = "UnaryOperator";
        TYPE_NAMES[(int)TokenType::ACCESS_OPERATOR] = "AccessOperator";
        TYPE_NAMES[(int)TokenType::IDENTIFIER] = "Identifier";
        TYPE_NAMES[(int)TokenType::RESERVED] = "ReservedWord";
        TYPE_NAMES[(int)TokenType::CALL_OPERATOR] = "CallOperator";
        TYPE_NAMES[(int)TokenType::UNDEFINED] = "Undefined";
        TYPE_NAMES[(int)TokenType::SEMICOLON] = "Semicolon";
        TYPE_NAMES[(int)TokenType::COMMA] = "Comma";
        TYPE_NAMES[(int)TokenType::LINE_BREAK] = "Linebreak";
    }

    std::ostream& operator<<(std::ostream& out, TokenType type) {
        return out << TYPE_NAMES[(int)type];
    }
}