//
// Created by Daniil Nedaiborsch on 21.04.2020.
//

#pragma once

#include <vector>
#include <memory>
#include <string>

#include <src/types.hpp>
#include "src/Slice.hpp"

#include <src/Statements/Statement.hpp>

using std::shared_ptr;
using std::string;

namespace clnt::states::arithm {

    typedef string (*Linter)(unique_ptr<Token> const&, unique_ptr<Token> const&);
    extern Linter LINTERS[255];
    void initLinters();

    string lintArithmetic(Slice<NonCopyableVector<unique_ptr<Token>>>);
    string lint(unique_ptr<Token> const&, unique_ptr<Token> const&);

    string lintSemicolon(unique_ptr<Token> const& token, unique_ptr<Token> const&);
    string lintBinaryOperator(unique_ptr<Token> const& token, unique_ptr<Token> const&);
    string lintUnaryOperator(unique_ptr<Token> const& token, unique_ptr<Token> const&);
    string lintAccessOperator(unique_ptr<Token> const& token, unique_ptr<Token> const&);
    string lintCallOperator(unique_ptr<Token> const& token, unique_ptr<Token> const&);
    string lintOperand(unique_ptr<Token> const& token, unique_ptr<Token> const&);
    string lintString(unique_ptr<Token> const& token, unique_ptr<Token> const&);
    string lintUndefined(unique_ptr<Token> const& token, unique_ptr<Token> const&);
    string lintReservedWord(unique_ptr<Token> const& token, unique_ptr<Token> const& last);
    string lintComma(unique_ptr<Token> const& token, unique_ptr<Token> const& last);
    string lintLineBreak(unique_ptr<Token> const& token, unique_ptr<Token> const& last);
    string lintSharp(unique_ptr<Token> const& token, unique_ptr<Token> const& last);
    string lintBackslash(unique_ptr<Token> const& token, unique_ptr<Token> const& last);
    string lintColon(unique_ptr<Token> const& token, unique_ptr<Token> const& last);
    string lintInit(unique_ptr<Token> const& token, unique_ptr<Token> const& last);
}
