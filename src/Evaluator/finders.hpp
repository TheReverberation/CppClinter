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
    typedef std::pair<Token*, size_t> (*TokenFinder) (Slice<std::vector<lex::Lexeme*>> const&, Token*);

    std::pair<Token*, size_t> findBlock(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findOperator(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findReserved(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findWord(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findCallOperator(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findSemicolon(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findLineBreak(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findComma(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findSharp(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findBackslash(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findQuestion(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findInitializer(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);
    std::pair<Token*, size_t> findComment(Slice<std::vector<lex::Lexeme*>> const& lexemes, Token* lastToken);

    // All token finders, inited in init();
    extern vector<TokenFinder> FINDERS;

    // Init constants
    void init();
}
