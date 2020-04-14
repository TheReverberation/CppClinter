//
// Created by Daniil Nedaiborsch on 14.04.2020.
//

#include "Lexer.hpp"


namespace clnt {

    Lexer::Lexer(vector<finders::Finder> finders): finders_(std::move(finders)) {}

    vector<shared_ptr<Lexeme>> Lexer::lexing(SString const& s) {
        vector<shared_ptr<Lexeme>> lexemes;

        auto lastLexeme = [&lexemes] () -> shared_ptr<Lexeme> {
            return !lexemes.empty() ? lexemes.back() : nullptr;
        };

        for (size_t i = 0; i < s.size();) {
            i += finders::findNonSpace(s.slice(i), {' ', '\t'});
            shared_ptr<Lexeme> lexeme = nullptr;
            for (auto& finder : finders_) {
                lexeme = finder(s.slice(i), lastLexeme());
                if (lexeme) {
                    break;
                }
            }
            if (lexeme) {
                lexemes.push_back(lexeme);
            } else {
                lexemes.emplace_back(new Lexeme(s.slice(i), LexemeType::UNDEFINED));
            }
            //std::cout << *lexemes.back() << std::endl;
            i += lexemes.back()->j;
        }

        return lexemes;
    }
}
