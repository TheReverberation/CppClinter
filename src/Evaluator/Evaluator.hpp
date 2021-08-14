#pragma once

#include <vector>
#include <memory>

#include "finders.hpp"
#include "src/Lexer/Lexeme.hpp"
#include "src/Slice.hpp"



namespace clnt::eval {
    using Tokens = std::vector<std::unique_ptr<Token>>;
    /*
     * Evaluator is giving a sense for lexemes, grouping it and identifying its exactly type.
     * Attributes:
     *     finders: vector of TokenFinders
     */
    class Evaluator {
    public:
        explicit Evaluator(std::vector<finders::TokenFinder> finders);
        std::vector<finders::TokenFinder> const finders;
        Tokens evaluate(Slice<lex::Lexemes> const& lexemes);
    };
}
