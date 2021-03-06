#include "Token.hpp"

namespace clnt::eval {

    Token::Token(TokenType type, Slice<vector<shared_ptr<lex::Lexeme>>> lexemes):
            type(type), lexemes(std::move(lexemes)) {}

    std::ostream& operator<<(std::ostream& out, Token const& t) {
        out << "<" << t.type << ", [";
        for (size_t i = 0; i < (int)t.lexemes.size() - 1; ++i) {
            out << *t.lexemes[i] << ", ";
        }
        return out << *t.lexemes[t.lexemes.size() - 1] << "]>";
    }


}