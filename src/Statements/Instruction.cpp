//
// Created by Daniil Nedaiborsch on 21.04.2020.
//

#include "Instruction.hpp"

namespace clnt::states {
    Instruction::Instruction(clnt::Slice<vector<Token*>> lexemes):
        Statement(StatementType::INSTRUCTION, move(lexemes)) {}


    pair<Statement*, size_t> Instruction::find(Slice<vector<Token*>> const& tokens) {
        size_t expresionEnd = arithm::findCompleteExpression(tokens);
        if (expresionEnd != 0 && expresionEnd < tokens.size()) {
            if (tokens[expresionEnd]->type == TokenType::SEMICOLON) {
                return {Statement::gc.make<Instruction>(tokens.slice(0, expresionEnd + 1)), expresionEnd + 1};
            }
        }
        return {nullptr, 0};
    }

    void Instruction::lint() const {
        _linted = arithm::lintArithmetic(tokens);
    }
}
