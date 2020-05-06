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

    typedef std::pair<shared_ptr<Token>, size_t> (*TokenFinder) (Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const&, shared_ptr<Token>);

    std::pair<shared_ptr<Token>, size_t> findBlock(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findOperator(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findReserved(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findWord(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findCallOperator(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findSemicolon(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findLineBreak(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);
    std::pair<shared_ptr<Token>, size_t> findComma(Slice<std::vector<std::shared_ptr<lex::Lexeme>>> const& lexemes, shared_ptr<Token> lastToken);

    extern vector<TokenFinder> FINDERS;
    void init();
}
