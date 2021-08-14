/*
 * Lexeme finders
 */

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

    /*
     * Finder is as function for finding lexemes in a string.
     * Returns:
     *      {lexeme_ptr, i}, where the lexeme contains tokens from 0 to i(excluding),
     *      returns {nullptr, 0} if lexeme is not found
     */
    using FoundLexeme = std::pair<std::unique_ptr<Lexeme>, size_t>;
    using LexemeFinder = FoundLexeme (*) (Slice<std::string> const&);

    FoundLexeme findName(Slice<std::string> const&);
    FoundLexeme findString(Slice<std::string> const&);
    FoundLexeme findBackslash(Slice<std::string> const&);
    FoundLexeme findOperator(Slice<std::string> const&);
    FoundLexeme findConstant(Slice<std::string> const&);
    FoundLexeme findComma(Slice<std::string> const&);
    FoundLexeme findColon(Slice<std::string> const&);
    FoundLexeme findSemicolon(Slice<std::string> const&);
    FoundLexeme findLinebreak(Slice<std::string>const&);
    FoundLexeme findQuestion(Slice<std::string> const&);
    FoundLexeme findOpenBracket(Slice<std::string> const&);
    FoundLexeme findCloseBracket(Slice<std::string> const&);
    FoundLexeme findSharp(Slice<std::string> const&);
    FoundLexeme findComment(Slice<std::string> const&);

    // List of all finders
    extern std::vector<LexemeFinder> FINDERS;
    
    std::vector<std::pair<char, char>> const bracketsSets = {
            {'(', ')'}, {'[', ']'}, {'{', '}'}
    };

    // Init constants
    void init();
}
