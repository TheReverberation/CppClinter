/*
 * Token finders
 */

#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <utility>

#include "Token.hpp"
#include "src/Slice.hpp"
#include "src/calphabet.hpp"

#include "Error/EvaluateException.hpp"

namespace clnt::eval::finders {

    /*
     * It is similar to LexemeFinder, but accepts last token needed to exactly determine token type.
     * Args:
     *      slice of lexemes, last token.
     * Returns:
     *      {token_ptr, i}, where token contain lexemes from 0 to i(excluding).
     * Throws:
     *      EvaluateException, see realisation
     */

    using FoundToken = std::pair<std::unique_ptr<Token>, size_t>;
    using TokenFinder = FoundToken (*) (Slice<lex::Lexemes> const&, std::unique_ptr<Token> const&);


    FoundToken findBlock(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findOperator(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findReserved(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findWord(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findCallOperator(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findSemicolon(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findLineBreak(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findComma(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findSharp(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findBackslash(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findQuestion(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findInitializer(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findComment(Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);

    // All token finders, inited in init();
    extern std::vector<TokenFinder> FINDERS;

    // Init constants
    void init();
}
