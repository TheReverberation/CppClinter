#pragma once

#include <vector>

#include <src/Slice.hpp>

#include "Statement.hpp"

namespace clnt::states {
    class Typedef: public Statement {
    public:
        explicit Typedef(Slice<eval::Tokens>);
        void lint() const override;
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<eval::Tokens> const&);
    };
}