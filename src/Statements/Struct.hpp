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
        Struct(Slice<NonCopyableVector<std::unique_ptr<Token>>>, NonCopyableVector<std::unique_ptr<Statement>>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<NonCopyableVector<unique_ptr<Token>>> const&);
        void lint() const override;
        NonCopyableVector<std::unique_ptr<Statement>> const statements;
    };
}
