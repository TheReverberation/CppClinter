#pragma once

#include <vector>

#include <src/Slice.hpp>
#include <src/Lexer/Lexeme.hpp>
#include <src/PrimeGC.hpp>

#include "TokenType.hpp"

using std::vector;

namespace clnt::eval {
    /*
     *  Token is similar to lexeme, it's also immutable type.
     */
    class Token {
    public:
        Token(TokenType type, Slice<vector<lex::Lexeme*>> lexemes);
        
        ~Token() {
            std::cout << "Token dest\n";
        }

        TokenType const type;
        Slice<vector<lex::Lexeme*>> const lexemes;

        void* operator new(size_t);

        static mem::PrimeGC<Token> gc;
    };

    std::ostream& operator<<(std::ostream& out, Token const& t);
}

