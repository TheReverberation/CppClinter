//
// Created by Daniil Nedaiborsch on 27.04.2020.
//

#pragma once

#include <memory>

#include "Statement.hpp"

#include "src/Evaluator/Token.hpp"

#include "Arithmetic/findCompleteExpression.hpp"
#include "Arithmetic/linters.hpp"

using clnt::eval::Token;
using clnt::eval::TokenType;
using std::make_unique;

namespace clnt::states {
    class Expression: public Statement {
    public:
        explicit Expression(Slice<eval::Tokens>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<eval::Tokens> const&);
        void lint() const override;
    };
}

