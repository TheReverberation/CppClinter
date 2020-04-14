//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#pragma once

#include <iostream>


namespace clnt {
    enum struct LexemeType: uint8_t {
        NAME, OPERATOR, OPEN_BRACKET, CLOSE_BRACKET, LINE_BREAK, QUESTION, CONSTANT,
        BACKSLASH, COMMA, UNDEFINED, COLON, SEMICOLON
    };

    std::ostream& operator<<(std::ostream& out, LexemeType type);
    void initTypeNames();
}
