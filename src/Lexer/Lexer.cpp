//
// Created by Daniil Nedaiborsch on 14.04.2020.
//

#include <src/calphabet.hpp>
#include "Lexer.hpp"

using std::vector;
using std::string;


namespace clnt::lex {

    Lexer::Lexer(vector<finders::LexemeFinder> finders): finders_(std::move(finders)) {}

    vector<Lexeme*> Lexer::lexing(Slice<string> const& s) {
        vector<Lexeme*> lexemes;

        auto lastLexeme = [&lexemes] () -> Lexeme* {
            return !lexemes.empty() ? lexemes.back() : nullptr;
        };

        for (size_t i = 0; i < s.size();) {
            i += finders::findNonSpace(s.slice(i), {' ', '\t'});
            Lexeme* lexeme = nullptr;
            size_t lexemeEnd = 0;
            for (auto& finder : finders_) {
                auto found = finder(s.slice(i));
                lexeme = found.first;
                lexemeEnd = found.second;
                if (lexeme) {
                    break;
                }
            }
            if (lexeme) {
                lexemes.push_back(lexeme);
            } else {
                throw err::UndefinedLexemeException();
                lexemes.emplace_back(new Lexeme(LexemeType::UNDEFINED, s.slice(i)));
                lexemeEnd = s.size() - i;
            }
            i += lexemeEnd;
        }

        return lexemes;
    }

    Lexeme::~Lexeme() {
        std::cout << "Lexeme destruction\n";
    }
}
