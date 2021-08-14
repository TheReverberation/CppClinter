#include "ElseStatement.hpp"
#include "Expression.hpp"
#include "src/Parser/Parser.hpp"

#include "IfElseStatement.hpp"
#include "IfStatement.hpp"
#include "Instruction.hpp"
#include "Block.hpp"

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::pair;
using std::string;
using std::static_pointer_cast;

using namespace clnt::eval;

namespace clnt::states {
    ElseStatement::ElseStatement(Slice<Tokens> tokens, vector<unique_ptr<Statement>> statements):
        Statement(StatementType::ELSE, move(tokens)), statements(move(statements)) {
    }


    pair<unique_ptr<Statement>, size_t> ElseStatement::find(Slice<Tokens> const& tokens) {
        if (tokens[0]->type == eval::TokenType::RESERVED && tokens[0]->lexemes[0]->source == string("else")) {
            vector<unique_ptr<Statement>> statements;
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
                //::cout << *found.first << ',' << found.second << '\n';
                // if found is not line break
                if (!(found.first->type == StatementType::EXPRESSION && found.first->tokens[0]->type == TokenType::LINE_BREAK)) {
                   statements.push_back(move(found.first));
                }
                i += found.second;
            }
            //::cout << "endElseFind: ";
            for (auto& s : statements) {
                //::cout << *s << '\n';
            }
            //::cout << "!!!!!!!!!!\n";
            return {make_unique<ElseStatement>(tokens.slice(0, i), move(statements)), i};
        }
        return {nullptr, 0};
    }

    void ElseStatement::lint() const {
        // todo: move, lazy lint
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
        _linted = accumulate;
    }
}
