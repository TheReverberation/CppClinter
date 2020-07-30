#include "Lexeme.hpp"

using std::string;
using std::make_shared;

namespace clnt::lex {
    Lexeme::Lexeme(LexemeType type, Slice<string> source): type(type), source(source) {}

    void* Lexeme::operator new(size_t size) {
        void* p = ::operator new(size);
        Lexeme::gc.link((Lexeme*)p);
        return p;
    }

    mem::PrimeGC<Lexeme> Lexeme::gc;

    std::ostream& operator<<(std::ostream& out, Lexeme const& l) {
        out << "(" << l.type << ", "; 
        if (l.type == LexemeType::LINE_BREAK) {
            out << "\\n";
        } else {
            out << l.source;
        }
        return out << ")";
    }
}
