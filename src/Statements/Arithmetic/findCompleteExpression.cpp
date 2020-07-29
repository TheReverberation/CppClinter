//
// Created by Daniil Nedaiborsch on 26.04.2020.
//

#include "findCompleteExpression.hpp"

namespace clnt::states::arithm {
    size_t findCompleteExpression(Slice<NonCopyableVector<shared_ptr<Token>>> const &tokens) {
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
