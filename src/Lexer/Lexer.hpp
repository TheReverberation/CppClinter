#pragma once

#include <vector>
#include <memory>


#include <src/util/Slice.hpp>

#include "UndefinedLexemeException.hpp"
#include "Lexeme.hpp"
#include "finders.hpp"




namespace clnt::lex {
    using Lexemes = std::vector<std::unique_ptr<Lexeme>>;
    /*
     * Lexer is an object find all lexemes in a string.
     * Attributes:
     *      finders_: list of lexeme finders
    */
    class Lexer {
    private:
        std::vector<finders::LexemeFinder> finders_;
    public:
        explicit Lexer(std::vector<finders::LexemeFinder>);
        /*
         * Args:
         *      s: code string
         * Returns:
         *      vector of lexemes
         * Note:
         *      Returns "Undefined" lexeme including in vector if lexer is not able to discover some code.
         */
        Lexemes lexing(util::Slice<std::string> const& s);
    };
}
