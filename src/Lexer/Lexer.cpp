//
// Created by Daniil Nedaiborsch on 14.04.2020.
//

#include <src/calphabet.hpp>
#include "Lexer.hpp"


using std::string;
using std::unique_ptr;
using std::move;
using std::make_unique;


namespace clnt::lex {

    Lexer::Lexer(Vector<finders::LexemeFinder> finders): finders_(std::move(finders)) {}

    Vector<unique_ptr<Lexeme>> Lexer::lexing(Slice<string> const& s) {
        Vector<unique_ptr<Lexeme>> lexemes;


        for (size_t i = 0; i < s.size();) {
            i += finders::findNonSpace(s.slice(i), {' ', '\t'});
            unique_ptr<Lexeme> lexeme = nullptr;
            size_t lexemeEnd = 0;
            for (auto& finder : finders_) {
                auto found = finder(s.slice(i));
                lexeme = move(found.first);
                lexemeEnd = found.second;
                if (lexeme) {
                    break;
                }
            }
            if (lexeme) {
                lexemes.push_back(move(lexeme));
            } else {
                lexemes.push_back(make_unique<Lexeme>(LexemeType::UNDEFINED, s.slice(i)));
                lexemeEnd = s.size() - i;
            }
            i += lexemeEnd;
        }

        return lexemes;
    }
}
