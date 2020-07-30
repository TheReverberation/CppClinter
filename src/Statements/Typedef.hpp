#pragma once

#include <vector>

#include <src/Slice.hpp>

#include "Statement.hpp"

namespace clnt::states {
    class Typedef: public Statement {
    public:
        Typedef(Slice<std::vector<Token*>>);
        void lint() const override;
        static std::pair<Statement*, size_t> find(Slice<vector<Token*>> const&);
    };
}