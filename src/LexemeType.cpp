//
// Created by Daniil Nedaiborsch on 14.04.2020.
//


#include "LexemeType.hpp"

#include <boost/format.hpp>

#include <string>

namespace {
    std::string typeName[255];
}

namespace clnt {

    void initTypeNames() {
        for (size_t i = 0; i < 255; ++i) {
            typeName[i] = "$(LexemeType)";
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
    }

    std::ostream& operator<<(std::ostream& out, LexemeType type) {
        return out << typeName[(int)type];
    }
}