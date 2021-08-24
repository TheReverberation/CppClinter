#include <utility>

#include "Evaluator.hpp"

using std::unique_ptr;
using std::make_unique;
using std::move;
using std::vector;

using clnt::lex::Lexeme;
using clnt::lex::Lexemes;
using clnt::util::Slice;
using clnt::util::makeSlice;

namespace clnt::eval {
    Evaluator::Evaluator(vector<finders::TokenFinder> finders): finders(move(finders)) {}
    
    Tokens Evaluator::evaluate(Slice<Lexemes> const& lexemes) {
        vector<unique_ptr<Token>> tokens;
        auto lastToken = [&tokens = std::as_const(tokens)] () -> unique_ptr<Token> const& {
            static std::unique_ptr<Token> nulluptr = nullptr;
            if (!tokens.empty()) {
                return tokens.back();
            } else {
                return nulluptr;
            }
        };

        for (size_t i = 0; i < lexemes.size(); ) {
            unique_ptr<Token> token = nullptr;
            size_t tokenEnd = 0;
            for (auto finder : finders) {
                auto found = finder(lexemes.slice(i), lastToken());
                token.reset(found.first.release());
                tokenEnd = found.second;
                if (token) {
                    break;
                }
            }
            if (token) {
                tokens.push_back(move(token));
            } else {
                tokens.push_back(make_unique<Token>(TokenType::UNDEFINED, lexemes.slice(i)));
                tokenEnd = lexemes.size() - i;
            }
            i += tokenEnd;
        }
        return tokens;
    }

}
