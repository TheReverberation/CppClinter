#include "Preprocessor.hpp"
#include "Arithmetic/linters.hpp"

#include <src/Evaluator/TokenType.hpp>
#include <src/accumulate.hpp>

#include <algorithm>

using std::move;
using std::copy;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::make_pair;
using std::back_inserter;

using clnt::eval::TokenType;


namespace clnt::states {
    Preprocessor::Preprocessor(Slice<vector<Token*>> tokens):
        Statement(StatementType::PREPROCESSOR, move(tokens)) {
    }


    pair<Statement*, size_t> Preprocessor::find(Slice<vector<Token*>> const& tokens) {
        if (tokens[0]->type == TokenType::SHARP) {
            size_t preprocessorEnd = 1;
            for (size_t i = 1; i < tokens.size();) {
                size_t lineEnd = std::find_if(tokens.begin() + i, tokens.end(),
                    [](Token* const& token) {
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
            return {Statement::gc.make<Preprocessor>(tokens.slice(0, preprocessorEnd)), preprocessorEnd};
        }
        return {nullptr, 0};
    }

    void Preprocessor::lint() const {
        size_t strBegin = tokens[0]->lexemes[0]->source.i();
        size_t strEnd = strBegin;
        shared_ptr<string const> code = tokens[0]->lexemes[0]->source.container();

        for (auto& token : tokens) {
            for (auto& lexeme : token->lexemes) {
                strEnd = lexeme->source.j();
                if (lexeme->source.container() != code) {
                    assert(false);
                }
            }
        }
        //std::cout << "strEnd: " << strEnd << '\n';
        copy(code->begin() + strBegin, code->begin() + strEnd, back_inserter<string>(_linted));
    }
}