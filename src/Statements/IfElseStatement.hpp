#pragma once

#include <utility>
#include <vector>

#include "Statement.hpp"

#include "IfStatement.hpp"
#include "ElseStatement.hpp"

namespace clnt::states {
    class IfElseStatement: public Statement {
    public:
        IfElseStatement(Slice<std::vector<Token*>>, Statement*, Statement*);
        static std::pair<Statement*, size_t> find(Slice<std::vector<Token*>> const&); 
        void lint() const override;
        Statement* const ifStatement;
        Statement* const elseStatement;
    };
}
