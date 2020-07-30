#include "Evaluator.hpp"

using clnt::lex::Lexeme;

namespace clnt::eval {
    Evaluator::Evaluator(vector<finders::TokenFinder> finders): finders(std::move(finders)) {}
    
    vector<Token*> Evaluator::evaluate(Slice<vector<Lexeme*>> lexemes) {
        vector<Token*> tokens;

        auto lastToken = [&tokens] () {
            return tokens.empty() ? nullptr : tokens.back();
        };

        for (size_t i = 0; i < lexemes.size(); ) {
            Token* token = nullptr;
            size_t tokenEnd = 0;
            for (auto finder : finders) {
                auto found = finder(lexemes.slice(i), lastToken());
                token = found.first;
                tokenEnd = found.second;
                if (token) {
                    break;
                }
            }
            if (token) {
                tokens.push_back(token);
            } else {
                tokens.push_back(new Token(TokenType::UNDEFINED, lexemes.slice(i)));
                tokenEnd = lexemes.size() - i;
            }
            i += tokenEnd;
        }
        return tokens;
    }

}
