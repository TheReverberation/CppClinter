#include "Evaluator.hpp"

using clnt::lex::Lexeme;

namespace clnt::eval {
    Evaluator::Evaluator(vector<finders::TokenFinder> finders): finders(std::move(finders)) {}
    
    vector<unique_ptr<Token>> Evaluator::evaluate(Slice<vector<unique_ptr<Lexeme>>> lexemes) {
        vector<unique_ptr<Token>> tokens;

        auto lastToken = [&tokens] () -> unique_ptr<Token> const& {
            return nullptr;
        };

        for (size_t i = 0; i < lexemes.size(); ) {
            unique_ptr<Token> token = nullptr;
            size_t tokenEnd = 0;
            for (auto finder : finders) {
                auto found = finder(lexemes.slice(i), lastToken());
                token = move(found.first);
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
