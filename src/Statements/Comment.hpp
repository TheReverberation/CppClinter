#pragma once

#include <src/util/Slice.hpp>

#include "Statement.hpp"

namespace clnt::states {
    class Comment: public Statement {
    public:
        Comment(util::Slice<eval::Tokens> tokens);
        void lint() const override;
        static std::pair<std::unique_ptr<Statement>, size_t> find(util::Slice<eval::Tokens> const&);
    };
}
