//
// Created by Daniil Nedaiborsch on 18.04.2020.
//

#include "Block.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"
#include "Struct.hpp"

using std::unique_ptr;
using std::make_unique;
using std::string;
using std::move;
using std::vector;
using std::pair;
using std::make_pair;

using clnt::eval::Token;
using clnt::eval::TokenType;
using clnt::eval::Tokens;

namespace clnt::states {
    Struct::Struct(Slice<Tokens> tokens, vector<unique_ptr<Statement>> statements):
        Statement(StatementType::STRUCT, move(tokens)), statements(move(statements))
    {}

    void Struct::lint() const {
        for (auto& state : statements) {
            state->lint();
        }
        string accumulate;
        for (size_t i = 0; i < statements.size(); ++i) {
            accumulate += statements[i]->linted();
            if (i + 1 < statements.size() && statements[i + 1]->linted() != ";") {
                accumulate += " ";
            }
        }
        _linted = move(accumulate);
    }

    pair<unique_ptr<Statement>, size_t> Struct::find(Slice<Tokens> const& tokens) {
        if (tokens[0]->type == eval::TokenType::RESERVED && tokens[0]->lexemes[0]->source == string("struct")) {
            vector<unique_ptr<Statement>> statements;
            auto [word, _] = Expression::find(tokens.slice(0, 1));
            assert(word);
            statements.emplace_back(move(word));

            parse::Parser parser({Instruction::find, Expression::find, Block::find});
            size_t i = 1;
            while (statements.back()->type != StatementType::INSTRUCTION) {
                auto found = parser.find(tokens.slice(i));
                assert(found.first != nullptr);
                //std::cout << *found.first << ',' << found.second << '\n';
                if (!(found.first->type == StatementType::EXPRESSION && found.first->tokens[0]->type == TokenType::LINE_BREAK)) {
                   statements.emplace_back(move(found.first));
                }
                i += found.second;
            }
            return {make_unique<Struct>(tokens.slice(0, i), move(statements)), i};
        }
        return {nullptr, 0};
    }
}
