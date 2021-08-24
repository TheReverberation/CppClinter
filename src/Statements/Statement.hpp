#pragma once

#include <cassert>
#include <memory>
#include <vector>
#include <utility>
#include <string>

#include <src/util/Slice.hpp>
#include <src/Lexer/Lexeme.hpp>
#include <src/Evaluator/Token.hpp>
#include <src/Evaluator/Evaluator.hpp>


#include "StatementType.hpp"

namespace clnt::states {

    /*
     * Base abstract class for all statements
     */
    class Statement {
    public:
        Statement(StatementType, util::Slice<eval::Tokens>);
        StatementType const type;
        util::Slice<eval::Tokens> mutable tokens;
        std::string const& linted() const;
        virtual void lint() const;
        virtual ~Statement() = default;
    protected:
        std::string mutable _linted;
    };

    std::ostream& operator<<(std::ostream& out, Statement const& s);

    // Statement finder, it's similar to LexemeFinder
    using Finder = std::pair<std::unique_ptr<Statement>, size_t> (*)(util::Slice<eval::Tokens> const&);
}
