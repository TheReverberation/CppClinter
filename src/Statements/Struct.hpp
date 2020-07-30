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
        Struct(Slice<std::vector<Token*>>, std::vector<Statement*>);
        static std::pair<Statement*, size_t> find(Slice<vector<Token*>> const&);
        void lint() const override;
        std::vector<Statement*> const statements;
    };
}
