#include "ElseStatement.hpp"

using std::unique_ptr;
using std::make_shared;
using std::string;

using namespace clnt::eval;

namespace clnt::states {
    ElseStatement::ElseStatement(Slice<NonCopyableVector<unique_ptr<Token>>> tokens, NonCopyableVector<unique_ptr<Statement>> statements):
        Statement(StatementType::ELSE, std::move(tokens)), statements(std::move(statements)) {
    }


    std::pair<std::unique_ptr<Statement>, size_t> ElseStatement::find(Slice<NonCopyableVector<unique_ptr<Token>>> const& tokens) {
        if (tokens[0]->type == eval::TokenType::RESERVED && tokens[0]->lexemes[0]->source == string("else")) {
            NonCopyableVector<unique_ptr<Statement>> statements;
            auto [word, _] = Expression::find(tokens.slice(0, 1));
            assert(word);
            statements.push_back(move(word));

            parse::Parser parser({IfElseStatement::find, IfStatement::find, Instruction::find, Expression::find, Block::find});
            size_t i = 1;

            auto checkType = [] (StatementType type) {
                return type == StatementType::EXPRESSION; 
            };

            while (checkType(statements.back()->type)) {
                auto found = parser.find(tokens.slice(i));
                assert(found.first != nullptr);
                std::cout << *found.first << ',' << found.second << '\n';
                // if found is not line break
                if (!(found.first->type == StatementType::EXPRESSION && found.first->tokens[0]->type == TokenType::LINE_BREAK)) {
                   statements.push_back(move(found.first));
                }
                i += found.second;
            }
            std::cout << "endElseFind: ";
            for (auto& s : statements) {
                std::cout << *s << '\n';
            }
            std::cout << "!!!!!!!!!!\n";
            return {make_unique<ElseStatement>(tokens.slice(0, i), statements), i};
        }
        return {nullptr, 0};
    }

    void ElseStatement::lint() const {
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
}
