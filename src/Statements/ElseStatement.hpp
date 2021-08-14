#pragma once

#include <algorithm>
#include <utility>

#include "Statement.hpp"

#include <src/Evaluator/Token.hpp>
#include <src/Evaluator/TokenType.hpp>
#include <src/Slice.hpp>

namespace clnt::states {
    class ElseStatement: public Statement {
    public:
        ElseStatement(Slice<eval::Tokens>, std::vector<std::unique_ptr<Statement>>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<eval::Tokens> const&);
        void lint() const override;
        std::vector<std::unique_ptr<Statement>> const statements;
    };
}
