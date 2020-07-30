#pragma once

#include <string>
#include <memory>

#include <src/Slice.hpp>
#include <src/PrimeGC.hpp>

#include "LexemeType.hpp"


namespace clnt::lex {
    class Lexeme {
    public:
        /*
         * Immutable class
         */
        Lexeme(Lexeme const&) = delete;
        Lexeme(Lexeme&&) = delete;
        Lexeme(LexemeType type, Slice<std::string>);
        ~Lexeme();

        void* operator new(size_t);

        Slice<std::string> const source;
        LexemeType const type;
        static mem::PrimeGC<Lexeme> gc;
    };

    std::ostream& operator<<(std::ostream& out, Lexeme const& l);
}



