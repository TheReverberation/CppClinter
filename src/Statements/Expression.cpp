#include <algorithm>
#include <iterator>

#include "Expression.hpp"

using std::pair;
using std::vector;
using std::move;
using std::unique_ptr;
using std::make_unique;
using std::make_move_iterator;
using std::copy_if;

using clnt::util::Slice;

using clnt::eval::Tokens;
using clnt::eval::Token;
using clnt::eval::TokenType;

namespace clnt::states {
    Expression::Expression(Slice<Tokens> tokens):
            Statement(StatementType::EXPRESSION, move(tokens)) {}

    pair<unique_ptr<Statement>, size_t> Expression::find(Slice<Tokens> const& tokens) {
        size_t expresionEnd = arithm::findCompleteExpression(tokens);
        if (expresionEnd != 0) {
            return {make_unique<Expression>(tokens.slice(0, expresionEnd)), expresionEnd};
        } else {
            return {nullptr, 0};
        }
    }

    void Expression::lint() const {
        if (tokens[0]->type != TokenType::LINE_BREAK) {
            Tokens tokensWithoutLineBreak;
            for (unique_ptr<Token>& token : tokens) {
                if (token->type != TokenType::LINE_BREAK) {
                    tokensWithoutLineBreak.push_back(move(token));
                }
            }
            _linted = arithm::lintArithmetic(move(tokensWithoutLineBreak));
        } else {
            assert(tokens.size() == 1);
            _linted = "\n";
        }
    }
}
