#pragma once

#include <memory>

#include <src/util/Slice.hpp>
#include <src/Evaluator/Token.hpp>

#include "Statement.hpp"
#include "Arithmetic/findCompleteExpression.hpp"
#include "Arithmetic/linters.hpp"


namespace clnt::states {
    class Expression: public Statement {
    public:
        explicit Expression(util::Slice<eval::Tokens>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(util::Slice<eval::Tokens> const&);
        void lint() const override;
    };
}

