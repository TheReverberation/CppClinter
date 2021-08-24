#pragma once

#include <memory>

#include <src/Evaluator/Evaluator.hpp>

#include "Statement.hpp"


#include "Arithmetic/findCompleteExpression.hpp"
#include "Arithmetic/linters.hpp"


namespace clnt::states {
    class Instruction: public Statement {
    public:
        explicit Instruction(util::Slice<eval::Tokens>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(util::Slice<eval::Tokens> const&);
        void lint() const override;
    };
}



