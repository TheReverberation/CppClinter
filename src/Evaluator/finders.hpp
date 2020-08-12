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
    typedef std::pair<shared_ptr<Token>, size_t> (*TokenFinder) (Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const&, shared_ptr<Token>);

    std::pair<shared_ptr<Token>, size_t> findBlock(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findOperator(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findReserved(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findWord(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findCallOperator(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findSemicolon(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findLineBreak(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findComma(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findSharp(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findBackslash(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findQuestion(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findInitializer(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findComment(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);

    // All token finders, inited in init();
    extern vector<TokenFinder> FINDERS;

    // Init constants
    void init();
}
