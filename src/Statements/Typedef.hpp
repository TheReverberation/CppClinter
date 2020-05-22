#pragma once

#include <vector>

#include <src/Slice.hpp>

#include "Statement.hpp"

namespace clnt::states {
    class Typedef: public Statement {
    public:
        Typedef(Slice<std::vector<shared_ptr<Token>>>);
        void lint() const override;
        static std::pair<std::shared_ptr<Statement>, size_t> find(Slice<vector<shared_ptr<Token>>> const&);
    };
}