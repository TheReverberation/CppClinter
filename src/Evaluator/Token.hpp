#pragma once

#include <vector>

#include "src/Slice.hpp"
#include "src/Lexer/Lexeme.hpp"

#include "TokenType.hpp"
#include <src/types.hpp>

using std::vector;
using std::unique_ptr;

namespace clnt::eval {
    class Token {
    public:
        Token(TokenType type, Slice<NonCopyableVector<unique_ptr<lex::Lexeme>>> lexemes);
        Token(Token const&) = default;
        Token(Token&&) = default;
        TokenType const type;
        Slice<NonCopyableVector<unique_ptr<lex::Lexeme>>> const lexemes;
    };

    std::ostream& operator<<(std::ostream& out, Token const& t);
}

