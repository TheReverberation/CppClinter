#pragma once

#include <vector>
#include <string>
#include <memory>

#include <src/util/Slice.hpp>
#include <src/Evaluator/Evaluator.hpp>
#include <src/Parser/Parser.hpp>
#include <src/Linter/Linter.hpp>


#include "Statement.hpp"

namespace clnt::states {
    class Block: public Statement {
    public:
        explicit Block(util::Slice<eval::Tokens>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(util::Slice<eval::Tokens> const&);
        void lint() const override;
    };
}



