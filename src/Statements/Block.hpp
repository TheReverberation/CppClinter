//
// Created by Daniil Nedaiborsch on 18.04.2020.
//

#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Statement.hpp"
#include "src/Slice.hpp"

#include "src/Evaluator/all.hpp"
#include "src/Parser/Parser.hpp"
#include "src/Linter/Linter.hpp"

namespace clnt::states {
    class Block: public Statement {
    public:
        Block(Slice<NonCopyableVector<std::unique_ptr<Token>>>);
        static std::pair<unique_ptr<Statement>, size_t> find(Slice<NonCopyableVector<std::unique_ptr<Token>>> const&);
        void lint() const override;
    };
}



