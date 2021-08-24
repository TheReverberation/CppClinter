#pragma once

#include <string>
#include <vector>
#include <memory>

#include <src/util/Slice.hpp>
#include <src/Parser/Parser.hpp>
#include <src/Evaluator/Evaluator.hpp>

#include "Statement.hpp"


namespace clnt::states {
    class Struct: public Statement {
    public:
        Struct(util::Slice<eval::Tokens>, std::vector<std::unique_ptr<Statement>>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(util::Slice<eval::Tokens> const&);
        void lint() const override;
        std::vector<std::unique_ptr<Statement>> const statements;
    };
}
