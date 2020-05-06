//
// Created by Daniil Nedaiborsch on 21.04.2020.
//

#include "Instruction.hpp"

namespace clnt::states {
    Instruction::Instruction(clnt::Slice<vector<shared_ptr<Token>>> lexemes):
        Statement(StatementType::INSTRUCTION, move(lexemes)) {}


    pair<shared_ptr<Statement>, size_t> Instruction::find(Slice<vector<shared_ptr<Token>>> const& tokens) {
        size_t expresionEnd = arithm::findCompleteExpression(tokens);
        if (expresionEnd != 0 && expresionEnd < tokens.size()) {
            if (tokens[expresionEnd]->type == TokenType::SEMICOLON) {
                return {make_shared<Instruction>(tokens.slice(0, expresionEnd + 1)), expresionEnd + 1};
            }
        }
        return {nullptr, 0};
    }

    void Instruction::lint() const {
        _linted = arithm::lintArithmetic(tokens);
    }
}
