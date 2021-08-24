#include <src/calphabet.hpp>
#include "Lexer.hpp"

using std::vector;
using std::string;
using std::unique_ptr;
using std::move;

using clnt::util::Slice;

namespace clnt::lex {

    Lexer::Lexer(vector<finders::LexemeFinder> finders): finders_(move(finders)) {}

    vector<unique_ptr<Lexeme>> Lexer::lexing(Slice<string> const& s) {
        vector<unique_ptr<Lexeme>> lexemes;

        for (size_t i = 0; i < s.size();) {
            i += finders::findNonSpace(s.slice(i), {' ', '\t'});
            unique_ptr<Lexeme> lexeme = nullptr;
            size_t lexemeEnd = 0;
            for (auto& finder : finders_) {
                auto found = finder(s.slice(i));
                lexeme.reset(found.first.release());
                lexemeEnd = found.second;
                if (lexeme) {
                    break;
                }
            }
            if (lexeme) {
                lexemes.push_back(move(lexeme));
            } else {
                lexemes.emplace_back(new Lexeme(LexemeType::UNDEFINED, s.slice(i)));
                lexemeEnd = s.size() - i;
            }
            i += lexemeEnd;
        }

        return lexemes;
    }
}
