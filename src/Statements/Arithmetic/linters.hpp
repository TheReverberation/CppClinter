//
// Created by Daniil Nedaiborsch on 21.04.2020.
//

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

    typedef string (*Linter)(shared_ptr<Token>, shared_ptr<Token>);
    extern Linter LINTERS[255];
    void initLinters();

    string lintArithmetic(Slice<vector<shared_ptr<Token>>>);
    string lint(shared_ptr<Token>, shared_ptr<Token>);

    string lintSemicolon(shared_ptr<Token> token, shared_ptr<Token>);
    string lintBinaryOperator(shared_ptr<Token>, shared_ptr<Token>);
    string lintUnaryOperator(shared_ptr<Token>, shared_ptr<Token>);
    string lintAccessOperator(shared_ptr<Token>, shared_ptr<Token>);
    string lintCallOperator(shared_ptr<Token>, shared_ptr<Token>);
    string lintOperand(shared_ptr<Token>, shared_ptr<Token>);
    string lintString(shared_ptr<Token>, shared_ptr<Token>);
    string lintUndefined(shared_ptr<Token>, shared_ptr<Token>);
    string lintReservedWord(shared_ptr<Token> token, shared_ptr<Token> last);
    string lintComma(shared_ptr<Token> token, shared_ptr<Token> last);
    string lintLineBreak(shared_ptr<Token> token, shared_ptr<Token> last);
    string lintSharp(shared_ptr<Token> token, shared_ptr<Token> last);
    string lintBackslash(shared_ptr<Token> token, shared_ptr<Token> last);
    string lintColon(shared_ptr<Token> token, shared_ptr<Token> last);
    string lintInit(shared_ptr<Token> token, shared_ptr<Token> last);
}
