#pragma once

#include <utility>
#include <vector>

#include "Statement.hpp"

#include "IfStatement.hpp"
#include "ElseStatement.hpp"

namespace clnt::states {
    class IfElseStatement: public Statement {
    public:
        IfElseStatement(Slice<std::vector<std::shared_ptr<Token>>>, std::shared_ptr<Statement>, std::shared_ptr<Statement>);
        static std::pair<std::shared_ptr<Statement>, size_t> find(Slice<std::vector<std::shared_ptr<Token>>> const&); 
        void lint() const override;
        std::shared_ptr<Statement> const ifStatement;
        std::shared_ptr<Statement> const elseStatement;
    };
}
