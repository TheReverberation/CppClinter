//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#pragma once

#include <cstddef>
#include <string>

#include "LexemeType.hpp"
#include "SString.hpp"

namespace clnt {
    struct Lexeme {
        Lexeme(SString const&, LexemeType, size_t, size_t);
        Lexeme(SString const&, LexemeType);
        Lexeme(Lexeme const&) = default;
        Lexeme(Lexeme&&) = default;
        SString source;
        LexemeType const type;
        size_t i, j;
    };
    std::ostream& operator<<(std::ostream&, Lexeme const&);
}


