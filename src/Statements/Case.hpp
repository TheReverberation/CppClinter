#pragma once

#include <vector>
#include <string>

#include <src/Slice.hpp>

#include "Statement.hpp"


namespace clnt::states {
    class Case: public Statement {
    public:
        Case(clnt::Slice<eval::Tokens>);
        void lint() const override;
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<eval::Tokens> const&);
    };
}



