#pragma once

#include <cassert>
#include <memory>
#include <vector>
#include <utility>
#include <string>

#include "StatementType.hpp"
#include "UndefinedLinterError.hpp"

#include "src/Slice.hpp"
#include "src/Lexer/Lexeme.hpp"
#include "src/Evaluator/Token.hpp"

#include "src/Evaluator/Evaluator.hpp"

namespace clnt::states {

    /*
     * Base abstract class for all statements
     */
    class Statement {
    public:
        Statement(StatementType, Slice<eval::Tokens>);
        StatementType const type;
        Slice<eval::Tokens> mutable tokens;
        std::string const& linted() const;
        virtual void lint() const;
        virtual ~Statement() = default;
    protected:
        std::string mutable _linted;
    };

    std::ostream& operator<<(std::ostream& out, Statement const& s);

    // Statement finder, it's similar to LexemeFinder
    using Finder = std::pair<std::unique_ptr<Statement>, size_t> (*)(Slice<eval::Tokens> const&);
}
