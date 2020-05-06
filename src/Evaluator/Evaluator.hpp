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



namespace clnt::eval {
    class Evaluator {
    public:
        Evaluator(vector<finders::TokenFinder> finders);
        vector<finders::TokenFinder> const finders;
        vector<shared_ptr<Token>> evaluate(Slice<vector<shared_ptr<lex::Lexeme>>> lexemes);
    };
}
