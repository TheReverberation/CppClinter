#pragma once

#include <utility>
#include <vector>

#include "Statement.hpp"

#include "IfStatement.hpp"
#include "ElseStatement.hpp"

namespace clnt::states {
    class IfElseStatement: public Statement {
    public:
        IfElseStatement(Slice<NonCopyableVector<std::unique_ptr<Token>>>, std::unique_ptr<Statement>, std::unique_ptr<Statement>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<NonCopyableVector<std::unique_ptr<Token>>> const&); 
        void lint() const override;
        std::unique_ptr<Statement> const ifStatement;
        std::unique_ptr<Statement> const elseStatement;
    };
}
