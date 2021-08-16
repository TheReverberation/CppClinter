//
// Created by Daniil Nedaiborsch on 14.04.2020.
//

#include <src/calphabet.hpp>
#include "Lexer.hpp"

using std::vector;
using std::string;
using std::unique_ptr;

namespace clnt::lex {

    Lexer::Lexer(vector<finders::LexemeFinder> finders): finders_(std::move(finders)) {}

    vector<shared_ptr<Lexeme>> Lexer::lexing(Slice<string> const& s) {
        vector<shared_ptr<Lexeme>> lexemes;

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
                throw err::UndefinedLexemeException();
                lexemes.emplace_back(new Lexeme(LexemeType::UNDEFINED, s.slice(i)));
                lexemeEnd = s.size() - i;
            }
            i += lexemeEnd;
        }

        return lexemes;
    }
}
