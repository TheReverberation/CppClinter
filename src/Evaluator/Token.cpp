#include "Token.hpp"

namespace clnt::eval {

    mem::PrimeGC<Token> Token::gc;

    Token::Token(TokenType type, Slice<vector<lex::Lexeme*>> lexemes):
            type(type), lexemes(std::move(lexemes)) {}


    void* Token::operator new(size_t size) {
        void* p = ::operator new(size);
        Token::gc.link((Token*)p);
        return p;
    }

    std::ostream& operator<<(std::ostream& out, Token const& t) {
        out << "<" << t.type << ", [";
        for (size_t i = 0; i < (int)t.lexemes.size() - 1; ++i) {
            out << *t.lexemes[i] << ", ";
        }
        return out << *t.lexemes[t.lexemes.size() - 1] << "]>";
    }


}