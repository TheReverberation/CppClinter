//
// Created by Daniil Nedaiborsch on 27.04.2020.
//

#include "Expression.hpp"
namespace clnt::states {
    Expression::Expression(clnt::Slice<vector<shared_ptr<Token>>> tokens):
            Statement(StatementType::EXPRESSION, move(tokens)) {}


    pair<shared_ptr<Statement>, size_t> Expression::find(Slice<vector<shared_ptr<Token>>> const& tokens) {
        size_t expresionEnd = arithm::findCompleteExpression(tokens);
        if (expresionEnd != 0) {
            return {make_shared<Expression>(tokens.slice(0, expresionEnd)), expresionEnd};
        } else {
            return {nullptr, 0};
        }
    }

    void Expression::lint() const {
        if (tokens[0]->type != TokenType::LINE_BREAK) {
            vector<shared_ptr<Token>> tokensWithoutLineBreak;
            std::copy_if(tokens.begin(), tokens.end(), std::back_inserter(tokensWithoutLineBreak),
                         [](shared_ptr<Token> const &token) {
                             return token->type != TokenType::LINE_BREAK;
                         });
            _linted = arithm::lintArithmetic(makeSlice(tokensWithoutLineBreak));
        } else {
            assert(tokens.size() == 1);
            _linted = "\n";
        }
    }
}
