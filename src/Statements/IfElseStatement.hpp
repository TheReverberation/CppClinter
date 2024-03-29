#pragma once

#include <utility>
#include <vector>

#include <src/util/Slice.hpp>

#include "Statement.hpp"
#include "IfStatement.hpp"
#include "ElseStatement.hpp"

namespace clnt::states {
    class IfElseStatement: public Statement {
    public:
        IfElseStatement(util::Slice<eval::Tokens>, std::unique_ptr<IfStatement>, std::unique_ptr<ElseStatement>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(util::Slice<eval::Tokens> const&);
        void lint() const override;
        std::unique_ptr<IfStatement> const ifStatement;
        std::unique_ptr<ElseStatement> const elseStatement;
    };
}
