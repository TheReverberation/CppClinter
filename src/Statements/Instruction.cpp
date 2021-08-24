#include "Instruction.hpp"

using std::pair;
using std::make_unique;
using std::unique_ptr;

using clnt::util::Slice;
using clnt::eval::Tokens;
using clnt::eval::TokenType;
using clnt::eval::Token;

namespace clnt::states {
    Instruction::Instruction(Slice<Tokens> lexemes):
        Statement(StatementType::INSTRUCTION, move(lexemes)) {}

    void printInstr(Instruction const& i) {
        std::cout << *i.tokens[0] << '\n';
    }

    pair<unique_ptr<Statement>, size_t> Instruction::find(Slice<Tokens> const& tokens) {
        size_t expresionEnd = arithm::findCompleteExpression(tokens);
        if (expresionEnd != 0 && expresionEnd < tokens.size()) {
            if (tokens[expresionEnd]->type == TokenType::SEMICOLON) {
                return {make_unique<Instruction>(tokens.slice(0, expresionEnd + 1)), expresionEnd + 1};
            }
        }
        return {nullptr, 0};
    }

    void Instruction::lint() const {
        _linted = arithm::lintArithmetic(tokens);
    }
}
