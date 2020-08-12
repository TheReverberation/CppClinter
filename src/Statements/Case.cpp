#include <src/Parser/Parser.hpp>
#include <src/Linter/Linter.hpp>

#include "Arithmetic/linters.hpp"
#include "Expression.hpp"
#include "Case.hpp"

using std::vector;
using std::shared_ptr;
using std::string;

using clnt::eval::Token;
using clnt::Slice;
using clnt::parse::Parser;
using clnt::lint::Linter;

namespace clnt::states {
    Case::Case(Slice<vector<shared_ptr<Token>>> tokens):
        Statement(StatementType::CASE, move(tokens))  {

    }

    pair<std::shared_ptr<Statement>, size_t> Case::find(Slice<vector<shared_ptr<Token>>> const& tokens) {
        if (tokens.size() == 0) {
            return {nullptr, 0};
        }
        auto const& firstWord = tokens[0]->lexemes[0]->source;

        if (firstWord == string("case") || firstWord == string("default")) {
            auto name = Expression::find(tokens.slice(0, 1)).first;
            vector<shared_ptr<Statement>> statements = {name};
            Parser parser(STATEMENT_FINDERS);

            size_t i = 1;
            size_t endToken = 1;
            while (statements.back() && statements.back()->type != StatementType::CASE) {
                auto found = parser.find(tokens.slice(i));
                statements.push_back(found.first);
                i += found.second;
                if (found.first && found.first->type != StatementType::CASE) {
                    endToken = i;
                }
            }
            statements.pop_back();
            return {make_shared<Case>(tokens.slice(0, endToken)), endToken};
        }
        return {nullptr, 0};
    }

    void Case::lint() const {
        size_t i = 0;
        while (tokens[i]->type != TokenType::COLON) {
            ++i;
        }
        ++i;
        string const firstStr = arithm::lintArithmetic(tokens.slice(0, i));

        Parser const parser(STATEMENT_FINDERS);
        /*
        std::cout << "case lint tokens: ";
        for (auto& now : tokens) {
            std::cout << *now << ", ";
        }
        std::cout << '\n';*/

        auto const statements = parser.parse(tokens.slice(i));

        for (auto& now : statements) {
            now->lint();
        }

        string linted = firstStr;
        if (statements[0]->linted() != "\n" && statements[0]->type != StatementType::BLOCK) {
            linted += "\n";
        } else {
            linted += " ";
        }


        for (size_t i = 0; i < statements.size(); ++i) {
            auto const& state = statements[i];
            //std::cout << "case lint state:s " << *state << '\n';
            if (state->type == StatementType::BLOCK) {
                linted += state->linted();
            } else if (state->type == StatementType::EXPRESSION || state->linted() == "\n") {
                if (i + 1 < statements.size()) {
                    linted += '\n';
                }
            } else {
                linted += "\t" + state->linted();
            }
            //std::cout << "\'" << linted << "\'\n";
            if (state->linted() != "\n" && i + 1 < statements.size() && statements[i + 1]->linted() != "\n") {
                linted += "\n";
            }
        }
        _linted = move(linted);
    }
}