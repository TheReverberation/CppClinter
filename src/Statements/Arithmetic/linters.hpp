/*
 * Package for linting arithmetic expressions for instance 'Expression' or 'Instruction'
 */

#pragma once

#include <vector>
#include <memory>
#include <string>

#include "src/Slice.hpp"
#include "src/Statements/Statement.hpp"


namespace clnt::states::arithm {

    using Linter = std::string (*)(std::unique_ptr<eval::Token> const&, std::unique_ptr<eval::Token> const&);
    extern Linter LINTERS[255];
    void initLinters();

    std::string lintArithmetic(Slice<eval::Tokens> const&);
    std::string lint(std::unique_ptr<eval::Token> const&, std::unique_ptr<eval::Token> const&);

    std::string lintSemicolon(std::unique_ptr<eval::Token> const& token, std::unique_ptr<eval::Token> const&);
    std::string lintBinaryOperator(std::unique_ptr<eval::Token> const&, std::unique_ptr<eval::Token> const&);
    std::string lintUnaryOperator(std::unique_ptr<eval::Token> const&, std::unique_ptr<eval::Token> const&);
    std::string lintAccessOperator(std::unique_ptr<eval::Token> const&, std::unique_ptr<eval::Token> const&);
    std::string lintCallOperator(std::unique_ptr<eval::Token> const&, std::unique_ptr<eval::Token> const&);
    std::string lintOperand(std::unique_ptr<eval::Token> const&, std::unique_ptr<eval::Token> const&);
    std::string lintString(std::unique_ptr<eval::Token> const&, std::unique_ptr<eval::Token> const&);
    std::string lintUndefined(std::unique_ptr<eval::Token> const&, std::unique_ptr<eval::Token> const&);
    std::string lintReservedWord(std::unique_ptr<eval::Token> const& token, std::unique_ptr<eval::Token> const& last);
    std::string lintComma(std::unique_ptr<eval::Token> const& token, std::unique_ptr<eval::Token> const& last);
    std::string lintLineBreak(std::unique_ptr<eval::Token> const& token, std::unique_ptr<eval::Token> const& last);
    std::string lintSharp(std::unique_ptr<eval::Token> const& token, std::unique_ptr<eval::Token> const& last);
    std::string lintBackslash(std::unique_ptr<eval::Token> const& token, std::unique_ptr<eval::Token> const& last);
    std::string lintColon(std::unique_ptr<eval::Token> const& token, std::unique_ptr<eval::Token> const& last);
    std::string lintInit(std::unique_ptr<eval::Token> const& token, std::unique_ptr<eval::Token> const& last);
    std::string lintComment(std::unique_ptr<eval::Token> const& token, std::unique_ptr<eval::Token> const& last);
}
