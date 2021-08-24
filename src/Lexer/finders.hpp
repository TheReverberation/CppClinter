/*
 * Lexeme finders
 */

#pragma once

#include <array>
#include <memory>
#include <vector>
#include <utility>

#include "Lexeme.hpp"

#include <src/util/Slice.hpp>

namespace clnt::lex::finders {
    bool isident(char c);
    size_t findNonSpace(util::Slice<std::string> const&, std::vector<char> const&);
    std::pair<size_t, size_t> findBrackets(util::Slice<std::string> const&, std::array<char, 2>);

    /*
     * Finder is as function for finding lexemes in a string.
     * Returns:
     *      {lexeme_ptr, i}, where the lexeme contains tokens from 0 to i(excluding),
     *      returns {nullptr, 0} if lexeme is not found
     */
    using FoundLexeme = std::pair<std::unique_ptr<Lexeme>, size_t>;
    using LexemeFinder = FoundLexeme (*) (util::Slice<std::string> const&);

    FoundLexeme findName(util::Slice<std::string> const&);
    FoundLexeme findString(util::Slice<std::string> const&);
    FoundLexeme findBackslash(util::Slice<std::string> const&);
    FoundLexeme findOperator(util::Slice<std::string> const&);
    FoundLexeme findConstant(util::Slice<std::string> const&);
    FoundLexeme findComma(util::Slice<std::string> const&);
    FoundLexeme findColon(util::Slice<std::string> const&);
    FoundLexeme findSemicolon(util::Slice<std::string> const&);
    FoundLexeme findLinebreak(util::Slice<std::string>const&);
    FoundLexeme findQuestion(util::Slice<std::string> const&);
    FoundLexeme findOpenBracket(util::Slice<std::string> const&);
    FoundLexeme findCloseBracket(util::Slice<std::string> const&);
    FoundLexeme findSharp(util::Slice<std::string> const&);
    FoundLexeme findComment(util::Slice<std::string> const&);

    // List of all finders
    extern std::vector<LexemeFinder> FINDERS;
    
    std::vector<std::pair<char, char>> const bracketsSets = {
            {'(', ')'}, {'[', ']'}, {'{', '}'}
    };

    // Init constants
    void init();
}
