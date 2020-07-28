//
// Created by Daniil Nedaiborsch on 19.04.2020.
//

#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <utility>

#include "src/Evaluator/Token.hpp"
#include "src/Slice.hpp"
#include "src/calphabet.hpp"





namespace clnt::eval::finders {

    typedef std::pair<unique_ptr<Token>, size_t> (*TokenFinder) (Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const&, unique_ptr<Token> const&);

    std::pair<unique_ptr<Token>, size_t> findBlock(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findOperator(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findReserved(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findWord(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findCallOperator(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findSemicolon(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findLineBreak(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findComma(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findSharp(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findBackslash(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findQuestion(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);
    std::pair<unique_ptr<Token>, size_t> findInitializer(Slice<std::vector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const&);

    extern vector<TokenFinder> FINDERS;
    void init();
}
