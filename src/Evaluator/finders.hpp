//
// Created by Daniil Nedaiborsch on 19.04.2020.
//

#pragma once

#include <algorithm>
#include <memory>
#include <utility>

#include "src/Evaluator/Token.hpp"
#include "src/Slice.hpp"
#include "src/calphabet.hpp"





namespace clnt::eval::finders {

    typedef std::pair<unique_ptr<Token>, size_t> (*TokenFinder) (Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const&, unique_ptr<Token> const&);

    std::pair<unique_ptr<Token>, size_t> findBlock(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findOperator(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findReserved(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findWord(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findCallOperator(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findSemicolon(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findLineBreak(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findComma(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findSharp(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findBackslash(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findQuestion(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findInitializer(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);

    extern Vector<TokenFinder> FINDERS;
    void init();
}
