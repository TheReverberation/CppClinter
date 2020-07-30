/*
 * Package for linting arithmetic expressions for instance 'Expression' or 'Instruction'
 */

#pragma once

#include <vector>
#include <memory>
#include <string>


#include "src/Slice.hpp"

#include "src/Statements/Statement.hpp"

using std::vector;
using std::shared_ptr;
using std::string;

namespace clnt::states::arithm {

    typedef string (*Linter)(Token*, Token*);
    extern Linter LINTERS[255];
    void initLinters();

    string lintArithmetic(Slice<vector<Token*>>);
    string lint(Token*, Token*);

    string lintSemicolon(Token* token, Token*);
    string lintBinaryOperator(Token*, Token*);
    string lintUnaryOperator(Token*, Token*);
    string lintAccessOperator(Token*, Token*);
    string lintCallOperator(Token*, Token*);
    string lintOperand(Token*, Token*);
    string lintString(Token*, Token*);
    string lintUndefined(Token*, Token*);
    string lintReservedWord(Token* token, Token* last);
    string lintComma(Token* token, Token* last);
    string lintLineBreak(Token* token, Token* last);
    string lintSharp(Token* token, Token* last);
    string lintBackslash(Token* token, Token* last);
    string lintColon(Token* token, Token* last);
    string lintInit(Token* token, Token* last);
    string lintComment(Token* token, Token* last);
}
