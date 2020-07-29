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
using std::make_shared;

namespace clnt::states {
    class Expression: public Statement {
    public:
        Expression(Slice<NonCopyableVector<unique_ptr<Token>>>);
        static pair<unique_ptr<Statement>, size_t> find(Slice<NonCopyableVector<unique_ptr<Token>>> const&);
        void lint() const override;
    };
}

