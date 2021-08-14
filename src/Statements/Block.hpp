//
// Created by Daniil Nedaiborsch on 18.04.2020.
//

#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Statement.hpp"
#include "src/Slice.hpp"

#include "src/Evaluator/Evaluator.hpp"
#include "src/Parser/Parser.hpp"
#include "src/Linter/Linter.hpp"

namespace clnt::states {
    class Block: public Statement {
    public:
        explicit Block(Slice<eval::Tokens>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<eval::Tokens> const&);
        void lint() const override;
    };
}



