#pragma once

#include <vector>
#include <string>
#include <utility>

#include <src/util/Slice.hpp>

#include "Statement.hpp"


namespace clnt::states {
    class Case: public Statement {
    public:
        Case(util::Slice<eval::Tokens>);
        void lint() const override;
        static std::pair<std::unique_ptr<Statement>, size_t> find(util::Slice<eval::Tokens> const&);
    };
}



