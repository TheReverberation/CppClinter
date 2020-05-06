//
// Created by Daniil Nedaiborsch on 21.04.2020.
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
    class Instruction: public Statement {
    public:
        Instruction(Slice<vector<shared_ptr<Token>>>);
        static pair<shared_ptr<Statement>, size_t> find(Slice<vector<shared_ptr<Token>>> const&);
        void lint() const override;
    };
}



