#include <vector>

#include "findCompleteExpression.hpp"

using std::vector;
using std::unique_ptr;
using std::make_unique;

using clnt::util::Slice;

using clnt::eval::Tokens;
using clnt::eval::Token;
using clnt::eval::TokenType;


namespace clnt::states::arithm {
    size_t findCompleteExpression(Slice<Tokens> const &tokens) {
        if (tokens[0]->type == TokenType::LINE_BREAK) {
            return 1;
        }

        auto check = [] (TokenType type) {
            return type != TokenType::SEMICOLON && type != TokenType::BLOCK;
        };

        size_t i = 0;
        for (; i < tokens.size() && check(tokens[i]->type); ++i);
        return i;
    }
}
