//
// Created by Daniil Nedaiborsch on 18.04.2020.
//

#include "Struct.hpp"

namespace clnt::states {
    Struct::Struct(Slice<std::vector<std::shared_ptr<Token>>> tokens, std::vector<std::shared_ptr<Statement>> statements):
        Statement(StatementType::STRUCT, std::move(tokens)), statements(std::move(statements))
    {}

    void Struct::lint() const {
        for (auto& state : statements) {
            state->lint();
        }
        string accumulate = "";
        for (size_t i = 0; i < statements.size(); ++i) {
            accumulate += statements[i]->linted();
            if (i + 1 < statements.size() && statements[i + 1]->linted() != ";") {
                accumulate += " ";
            }
        }
        _linted = accumulate;
    }

    std::pair<std::shared_ptr<Statement>, size_t> Struct::find(Slice<vector<shared_ptr<Token>>> const& tokens) {
        if (tokens[0]->type == eval::TokenType::RESERVED && tokens[0]->lexemes[0]->source == string("struct")) {
            vector<shared_ptr<Statement>> statements;
            auto [word, _] = Expression::find(tokens.slice(0, 1));
            assert(word);
            statements.push_back(word);

            parse::Parser parser({Instruction::find, Expression::find, Block::find});
            size_t i = 1;
            while (statements.back()->type != StatementType::INSTRUCTION) {
                auto found = parser.find(tokens.slice(i));
                assert(found.first != nullptr);
                //std::cout << *found.first << ',' << found.second << '\n';
                if (!(found.first->type == StatementType::EXPRESSION && found.first->tokens[0]->type == TokenType::LINE_BREAK)) {
                   statements.push_back(found.first);
                }
                i += found.second;
            }
            return {make_shared<Struct>(tokens.slice(0, i), statements), i};
        }
        return {nullptr, 0};
    }
}
