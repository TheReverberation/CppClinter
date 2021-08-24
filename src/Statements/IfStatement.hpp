#pragma once

#include <algorithm>
#include <utility>


#include <src/Evaluator/Token.hpp>
#include <src/Evaluator/TokenType.hpp>
#include <src/util/Slice.hpp>

#include "Statement.hpp"

namespace clnt::states {
    class IfStatement: public Statement {
    public:
        IfStatement(util::Slice<eval::Tokens>, std::vector<std::unique_ptr<Statement>>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(util::Slice<eval::Tokens> const&);
        void lint() const override;
        std::vector<std::unique_ptr<Statement>> const statements;
    };
}
