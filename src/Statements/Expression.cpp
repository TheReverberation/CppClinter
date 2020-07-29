//
// Created by Daniil Nedaiborsch on 27.04.2020.
//

#include "Expression.hpp"
namespace clnt::states {
    Expression::Expression(clnt::Slice<NonCopyableVector<unique_ptr<Token>>> tokens):
            Statement(StatementType::EXPRESSION, move(tokens)) {}


    pair<unique_ptr<Statement>, size_t> Expression::find(Slice<NonCopyableVector<unique_ptr<Token>>> const& tokens) {
        size_t expresionEnd = arithm::findCompleteExpression(tokens);
        if (expresionEnd != 0) {
            unique_ptr<Statement> a(new Expression(tokens.slice(0, expresionEnd)));
            return {move(a), expresionEnd};
        } else {
            return {nullptr, 0};
        }
    }

    void Expression::lint() const {
        if (tokens[0]->type != TokenType::LINE_BREAK) {
            NonCopyableVector<unique_ptr<Token>&> tokensWithoutLineBreak;
            for (size_t i = 0; i < tokens.size(); ++i) {
                tokensWithoutLineBreak.push_back(tokens[i]);
            }
//            std::copy_if(std::make_move_iterator(tokens.begin()), std::make_move_iterator(tokens.end()), std::back_inserter(tokensWithoutLineBreak),
//                         [](unique_ptr<Token> const &token) {
//                             return token->type != TokenType::LINE_BREAK;
//                         });
            _linted = arithm::lintArithmetic(makeSlice(move(tokensWithoutLineBreak)));
        } else {
            assert(tokens.size() == 1);
            _linted = "\n";
        }
    }
}
