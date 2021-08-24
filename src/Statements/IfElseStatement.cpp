#include "IfElseStatement.hpp"
#include "Expression.hpp"
#include <src/Parser/Parser.hpp>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::make_pair;
using std::move;
using std::pair;

using clnt::util::Slice;
using clnt::eval::Tokens;
using clnt::eval::Token;
using clnt::eval::TokenType;

namespace clnt::states {
    IfElseStatement::IfElseStatement(Slice<Tokens> tokens,
                                     unique_ptr<IfStatement> ifState, unique_ptr<ElseStatement> elseState):
    Statement(StatementType::IFELSE, move(tokens)), ifStatement(move(ifState)), elseStatement(move(elseState)) {}

    pair<unique_ptr<Statement>, size_t> IfElseStatement::find(Slice<Tokens> const& tokens) {
        size_t i = 0, end = 0;
        auto ifstate =  IfStatement::find(tokens);
        if (ifstate.first) {
            i = ifstate.second;
            end = i;
            parse::Parser parser({Expression::find});
            pair<unique_ptr<Statement>, size_t> found = parser.find(tokens.slice(i));
            while (i < tokens.size() && found.first && found.first->tokens[0]->type == TokenType::LINE_BREAK) {
                i += found.second;
                found = parser.find(tokens.slice(i));
            }

            auto elsestate = ElseStatement::find(tokens.slice(i));
            if (elsestate.first) {
                // std::cout << "ElseFound\n" << "";
                i += elsestate.second;
                end = i;
                unique_ptr<IfStatement> ifstate_casted(dynamic_cast<IfStatement*>(ifstate.first.release()));
                unique_ptr<ElseStatement> elsestate_casted(dynamic_cast<ElseStatement*>(ifstate.first.release()));
                return {make_unique<IfElseStatement>(tokens.slice(0, end), move(ifstate_casted), move(elsestate_casted)), end};
            }
       }
        return {nullptr, 0};
    }

    void IfElseStatement::lint() const {
        _linted = "";
        ifStatement->lint();
        _linted += ifStatement->linted();
        if (elseStatement) {
            elseStatement->lint();
            _linted += " " + elseStatement->linted();
        }
    }

}
