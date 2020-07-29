//
// Created by Daniil Nedaiborsch on 19.04.2020.
//

#pragma once

#include <vector>
#include <memory>

#include "finders.hpp"
#include "src/Lexer/Lexeme.hpp"
#include "src/Slice.hpp"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;


namespace clnt::eval {
    class Evaluator {
    public:
        Evaluator(vector<finders::TokenFinder> finders);
        vector<finders::TokenFinder> const finders;
        vector<unique_ptr<Token>> evaluate(Slice<vector<unique_ptr<lex::Lexeme>>> lexemes);
    };
}
