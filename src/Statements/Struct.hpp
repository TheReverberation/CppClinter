//
// Created by Daniil Nedaiborsch on 18.04.2020.
//

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "src/Parser/Parser.hpp"
#include "src/Linter/Linter.hpp"
#include "src/Evaluator/all.hpp"

#include "Statement.hpp"
#include "src/Lexer/Lexeme.hpp"
#include "src/Slice.hpp"



namespace clnt::states {
    class Struct: public Statement {
    public:
        Struct(Slice<std::vector<std::shared_ptr<Token>>>, std::vector<std::shared_ptr<Statement>>);
        static std::pair<std::shared_ptr<Statement>, size_t> find(Slice<vector<shared_ptr<Token>>> const&);
        void lint() const override;
        std::vector<std::shared_ptr<Statement>> const statements;
    };
}
