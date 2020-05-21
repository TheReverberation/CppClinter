//
// Created by Daniil Nedaiborsch on 14.04.2020.
//

#include <string>

#include "LexemeType.hpp"


namespace {
    std::string typeName[255];
}

namespace clnt::lex {

    void initTypeNames() {
        for (size_t i = 0; i < 255; ++i) {
            typeName[i] = "$(LexemeTypeName)";
        }

        typeName[(int)LexemeType::NAME] = "Name";
        typeName[(int)LexemeType::OPERATOR] = "Operator";
        typeName[(int)LexemeType::OPEN_BRACKET] = "OpenBracket";
        typeName[(int)LexemeType::CLOSE_BRACKET] = "CloseBracket";
        typeName[(int)LexemeType::LINE_BREAK] = "LineBreak";
        typeName[(int)LexemeType::QUESTION] = "Question";
        typeName[(int)LexemeType::CONSTANT] = "Constant";
        typeName[(int)LexemeType::BACKSLASH] = "Backslash";
        typeName[(int)LexemeType::COMMA] = "Comma";
        typeName[(int)LexemeType::UNDEFINED] = "Undefined";
        typeName[(int)LexemeType::COLON] = "Colon";
        typeName[(int)LexemeType::SEMICOLON] = "Semicolon";
        typeName[(int)LexemeType::SHARP] = "Sharp";
    }

    std::ostream& operator<<(std::ostream& out, LexemeType type) {
        return out << typeName[(int)type];
    }
}