#pragma once

#include <vector>

#include "src/Slice.hpp"
#include "src/Lexer/Lexeme.hpp"

#include "TokenType.hpp"

using std::vector;

namespace clnt::eval {
    class Token {
    public:
        Token(TokenType type, Slice<vector<shared_ptr<lex::Lexeme>>> lexemes);
        Token(Token const&) = default;
        Token(Token&&) = default;
        TokenType const type;
        Slice<vector<shared_ptr<lex::Lexeme>>> const lexemes;
    };

    std::ostream& operator<<(std::ostream& out, Token const& t);
}

