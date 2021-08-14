#pragma once

#include <vector>

#include "src/Slice.hpp"
#include "src/Lexer/Lexeme.hpp"
#include "src/Lexer/Lexer.hpp"

#include "TokenType.hpp"


namespace clnt::eval {
    /*
     *  Token is similar to lexeme, it's also immutable type.
     */
    class Token {
    public:
        Token(TokenType type, Slice<lex::Lexemes> lexemes);
        Token(Token const&) = default;
        Token(Token&&) = default;
        TokenType const type;
        Slice<lex::Lexemes> const lexemes;
    };

    std::ostream& operator<<(std::ostream& out, Token const& t);
}

