#include "IfStatement.hpp"
#include "Instruction.hpp"
#include "Block.hpp"

#include "Expression.hpp"
#include "src/Parser/Parser.hpp"

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::string;


using namespace clnt::eval;
using clnt::util::Slice;

namespace clnt::states {
    IfStatement::IfStatement(Slice<Tokens> tokens, vector<unique_ptr<Statement>> statements):
        Statement(StatementType::IF, std::move(tokens)), statements(std::move(statements)) {
    }


    std::pair<std::unique_ptr<Statement>, size_t> IfStatement::find(Slice<Tokens> const& tokens) {
        if (tokens[0]->type == eval::TokenType::RESERVED && tokens[0]->lexemes[0]->source == string("if")) {
            vector<unique_ptr<Statement>> statements;
            auto [word, _] = Expression::find(tokens.slice(0, 1));
            assert(word);
            statements.emplace_back(move(word));
            auto [condition, _2] = Expression::find(tokens.slice(1, 2));
            assert(condition);
            statements.emplace_back(move(condition));
            parse::Parser parser({Instruction::find, Expression::find, Block::find});
            size_t i = 2;
            while (statements.back()->type != StatementType::INSTRUCTION && statements.back()->type != StatementType::BLOCK) {
                auto found = parser.find(tokens.slice(i));
                assert(found.first != nullptr);
                //std::cout << *found.first << ',' << found.second << '\n';
                // if found is not line break
                if (!(found.first->type == StatementType::EXPRESSION && found.first->tokens[0]->type == TokenType::LINE_BREAK)) {
                   statements.emplace_back(move(found.first));
                }
                i += found.second;
            }
            return {make_unique<IfStatement>(tokens.slice(0, i), move(statements)), i};
        }
        return {nullptr, 0};
    }

    void IfStatement::lint() const {
        for (auto& state : statements) {
            state->lint();
        }
        string accumulate = "";
        accumulate += statements[0]->linted() + " ";
        accumulate += statements[1]->linted();
        if (statements[2]->type == StatementType::INSTRUCTION) {
            accumulate += "\n\t";
        } else {
            accumulate += " ";
        }
        for (size_t i = 2; i < statements.size(); ++i) {
            accumulate += statements[i]->linted();
            if (i + 1 < statements.size() && statements[i + 1]->linted() != ";") {
                accumulate += " ";
            }
        }
        _linted = accumulate;
    }

}
