//
// Created by Daniil Nedaiborsch on 19.04.2020.
//

#pragma once

#include <vector>
#include <memory>

#include "finders.hpp"
#include "src/Lexer/Lexeme.hpp"
#include "src/Slice.hpp"

using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;


namespace clnt::eval {
    class Evaluator {
    public:
        Evaluator(Vector<finders::TokenFinder> finders);
        Vector<finders::TokenFinder> const finders;
        NonCopyableVector<unique_ptr<Token>> evaluate(Slice<NonCopyableVector<unique_ptr<lex::Lexeme>>> lexemes);
    };
}
