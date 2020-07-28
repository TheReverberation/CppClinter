#pragma once

#include <string>
#include <memory>

#include <src/Slice.hpp>
#include <src/types.hpp>

#include "LexemeType.hpp"


namespace clnt::lex {
    class Lexeme {
    public:
        Lexeme(Lexeme const&) = delete;
        Lexeme(Lexeme&&) = delete;
        Lexeme(LexemeType type, Slice<std::string>);
        Slice<std::string> const source;
        LexemeType const type;
    };

    std::ostream& operator<<(std::ostream& out, Lexeme const& l);
}



