#include "Preprocessor.hpp"
#include "Arithmetic/linters.hpp"

#include <src/Evaluator/TokenType.hpp>
#include <src/accumulate.hpp>

using std::move;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::make_pair;
using clnt::eval::TokenType;


namespace clnt::states {
    Preprocessor::Preprocessor(Slice<vector<shared_ptr<Token>>> tokens):
        Statement(StatementType::PREPROCESSOR, move(tokens)) {
    }


    pair<shared_ptr<Statement>, size_t> Preprocessor::find(Slice<vector<shared_ptr<Token>>> const& tokens) {
        if (tokens[0]->type == TokenType::SHARP) {
            size_t preprocessorEnd = 1;
            for (size_t i = 1; i < tokens.size();) {
                size_t lineEnd = std::find_if(tokens.begin() + i, tokens.end(),
                    [](shared_ptr<Token> const& token) {
                        return token->type == TokenType::LINE_BREAK;
                    }
                ) - tokens.begin();
                preprocessorEnd = lineEnd;
                i = preprocessorEnd + 1;

                // while line end with backslash
                if (tokens[lineEnd - 1]->type != TokenType::BACKSLASH) {
                    break;
                }
            }
            return {make_shared<Preprocessor>(tokens.slice(0, preprocessorEnd)), preprocessorEnd};
        }
        return {nullptr, 0};
    }

    void Preprocessor::lint() const {
        _linted = arithm::lintArithmetic(tokens);
    }
}