/*
 * Token finders
 */

#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <utility>

#include <src/util/Slice.hpp>
#include <src/calphabet.hpp>
#include <src/Lexer/Lexer.hpp>

#include "Token.hpp"

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
    using TokenFinder = FoundToken (*) (util::Slice<lex::Lexemes> const&, std::unique_ptr<Token> const&);


    FoundToken findBlock(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findOperator(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findReserved(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findWord(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findCallOperator(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findSemicolon(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findLineBreak(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findComma(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findSharp(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findBackslash(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findQuestion(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findInitializer(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);
    FoundToken findComment(util::Slice<lex::Lexemes> const& lexemes, std::unique_ptr<Token> const& lastToken);

    // All token finders, inited in init();
    extern std::vector<TokenFinder> FINDERS;

    // Init constants
    void init();
}
