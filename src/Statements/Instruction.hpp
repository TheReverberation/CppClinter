//
// Created by Daniil Nedaiborsch on 21.04.2020.
//

#pragma once

#include <memory>

#include "Statement.hpp"

#include "src/Evaluator/Token.hpp"

#include "Arithmetic/findCompleteExpression.hpp"
#include "Arithmetic/linters.hpp"


namespace clnt::states {
    class Instruction: public Statement {
    public:
        explicit Instruction(Slice<eval::Tokens>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<eval::Tokens> const&);
        void lint() const override;
    };
}



