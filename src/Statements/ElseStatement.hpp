#pragma once

#include <algorithm>
#include <utility>


#include "Statement.hpp"

#include <src/Statements/all.hpp>
#include <src/Evaluator/Token.hpp>
#include <src/Evaluator/TokenType.hpp>
#include <src/Slice.hpp>

namespace clnt::states {
    class ElseStatement: public Statement {
    public:
        ElseStatement(Slice<NonCopyableVector<std::unique_ptr<Token>>>, NonCopyableVector<unique_ptr<Statement>>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<NonCopyableVector<std::unique_ptr<Token>>> const&);
        void lint() const override;
        NonCopyableVector<unique_ptr<Statement>> const statements;
    };
}
