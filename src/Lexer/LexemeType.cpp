#include <algorithm>
#include <array>
#include <limits>
#include <string>

#include "LexemeType.hpp"

namespace {
    std::array<std::string, 255> typeName;
}

namespace clnt::lex {

    void initTypeNames() {        
        std::fill(typeName.begin(), typeName.end(), "$(LexemeTypeName)");

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
        typeName[(int)LexemeType::COMMENT] = "Comment";
    }

    std::string getLexemeTypeName(LexemeType type) {
        return typeName[static_cast<std::size_t>(type)];
    }

    std::ostream& operator<<(std::ostream& out, LexemeType type) {
        return out << getLexemeTypeName(type);
    }
}
