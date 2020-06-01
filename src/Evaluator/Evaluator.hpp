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
    /*
     * Evaluator is giving a sense for lexemes, grouping it and identifying its exactly type.
     * Attributes:
     *     finders: vector of TokenFinders
     */
    class Evaluator {
    public:
        Evaluator(vector<finders::TokenFinder> finders);
        vector<finders::TokenFinder> const finders;
        vector<shared_ptr<Token>> evaluate(Slice<vector<shared_ptr<lex::Lexeme>>> lexemes);
    };
}
