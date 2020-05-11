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
        ElseStatement(Slice<std::vector<std::shared_ptr<Token>>>, std::vector<shared_ptr<Statement>>);
        static std::pair<std::shared_ptr<Statement>, size_t> find(Slice<std::vector<std::shared_ptr<Token>>> const&);
        void lint() const override;
        std::vector<shared_ptr<Statement>> const statements;
    };
}
