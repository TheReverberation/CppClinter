//
// Created by Daniil Nedaiborsch on 19.04.2020.
//

#include "Evaluator.hpp"

using clnt::lex::Lexeme;

namespace clnt::eval {
    Evaluator::Evaluator(vector<finders::TokenFinder> finders): finders(std::move(finders)) {}
    
    vector<shared_ptr<Token>> Evaluator::evaluate(Slice<vector<shared_ptr<Lexeme>>> lexemes) {
        vector<shared_ptr<Token>> tokens;

        auto lastToken = [&tokens] () {
            return tokens.empty() ? nullptr : tokens.back();
        };

        for (size_t i = 0; i < lexemes.size(); ) {
            shared_ptr<Token> token = nullptr;
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
                tokens.push_back(make_shared<Token>(TokenType::UNDEFINED, lexemes.slice(i)));
                tokenEnd = lexemes.size() - i;
            }
            i += tokenEnd;
        }
        return tokens;
    }

}