#pragma once

#include <src/Slice.hpp>

#include "Statement.hpp"

namespace clnt::states {
    class Comment: public Statement {
    public:
        Comment(Slice<std::vector<std::shared_ptr<eval::Token>>>);
        void lint() const override;
        static std::pair<std::shared_ptr<Statement>, size_t> find(Slice<std::vector<std::shared_ptr<eval::Token>>> const&);
    };
}