#pragma once

#include <algorithm>
#include <utility>


#include "Statement.hpp"

#include <src/Statements/all.hpp>
#include <src/Evaluator/Token.hpp>
#include <src/Evaluator/TokenType.hpp>
#include <src/Slice.hpp>

namespace clnt::states {
    class IfStatement: public Statement {
    public:
        IfStatement(Slice<std::vector<Token*>>, std::vector<Statement*>);
        static std::pair<Statement*, size_t> find(Slice<std::vector<Token*>> const&);
        void lint() const override;
        std::vector<Statement*> const statements;
    };
}
