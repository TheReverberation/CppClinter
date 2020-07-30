#include "IfElseStatement.hpp"

#include <src/Parser/Parser.hpp>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::make_pair;
using std::move;
using std::pair;

namespace clnt::states {
    IfElseStatement::IfElseStatement(Slice<vector<Token*>> tokens,
                                     Statement* ifState, Statement* elseState):
    Statement(StatementType::IFELSE, move(tokens)), ifStatement(move(ifState)), elseStatement(move(elseState)) {}

    pair<Statement*, size_t> IfElseStatement::find(Slice<vector<Token*>> const& tokens) {
        size_t i = 0, end = 0;
        auto ifstate = IfStatement::find(tokens);
        if (ifstate.first) {
            i = ifstate.second;
            end = i;
            parse::Parser parser({Expression::find});
            pair<Statement*, size_t> found = parser.find(tokens.slice(i)); 
            while (i < tokens.size() && found.first && found.first->tokens[0]->type == TokenType::LINE_BREAK) {
                i += found.second;
                found = parser.find(tokens.slice(i));
            }

            auto elsestate = ElseStatement::find(tokens.slice(i));
            if (elsestate.first) {
                // std::cout << "ElseFound\n" << "";
                i += elsestate.second;
                end = i;
                return {Statement::gc.make<IfElseStatement>(tokens.slice(0, end), ifstate.first, elsestate.first), end};
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
