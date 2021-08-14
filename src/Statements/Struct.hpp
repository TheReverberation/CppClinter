//
// Created by Daniil Nedaiborsch on 18.04.2020.
//

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "src/Parser/Parser.hpp"
#include "src/Evaluator/Evaluator.hpp"

#include "Statement.hpp"
#include "src/Slice.hpp"



namespace clnt::states {
    class Struct: public Statement {
    public:
        Struct(Slice<eval::Tokens>, std::vector<std::unique_ptr<Statement>>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<eval::Tokens> const&);
        void lint() const override;
        std::vector<std::unique_ptr<Statement>> const statements;
    };
}
