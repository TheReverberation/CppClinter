#include "Token.hpp"

using std::vector;
using std::ostream;
using std::move;

using clnt::util::Slice;
using clnt::lex::Lexemes;

namespace clnt::eval {

    Token::Token(TokenType type, Slice<Lexemes> lexemes):
            type(type), lexemes(move(lexemes)) {}

    std::ostream& operator<<(std::ostream& out, Token const& t) {
        out << "<" << t.type << ", [";
        for (size_t i = 0; i < (int)t.lexemes.size() - 1; ++i) {
            out << *t.lexemes[i] << ", ";
        }
        return out << *t.lexemes[t.lexemes.size() - 1] << "]>";
    }


}
