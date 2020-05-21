//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#pragma once

#include <memory>
#include <vector>
#include <utility>

#include "src/Slice.hpp"
#include "Lexeme.hpp"


namespace clnt::lex::finders {
    bool isident(char c);

    size_t findNonSpace(Slice<std::string> const&, std::vector<char> const&);
    std::pair<size_t, size_t> findBrackets(Slice<std::string> const&, char[2]);

    // every finder returns {nullptr, 0} if lexeme don't exist
    typedef std::pair<std::shared_ptr<Lexeme>, size_t> (*LexemeFinder) (Slice<std::string> const&);

    std::pair<std::shared_ptr<Lexeme>, size_t> findName(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findString(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findBackslash(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findOperator(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findConstant(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findComma(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findColon(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findSemicolon(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findLinebreak(Slice<std::string>const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findQuestion(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findOpenBracket(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findCloseBracket(Slice<std::string> const&);
    std::pair<std::shared_ptr<Lexeme>, size_t> findSharp(Slice<std::string> const&);

    extern std::vector<LexemeFinder> FINDERS;
    std::vector<std::pair<char, char>> const bracketsSets = {
            {'(', ')'}, {'[', ']'}, {'{', '}'}
    };
    void init();
}
