#pragma once

#include "src/Slice.hpp"

#include "Statement.hpp"

namespace clnt::states {
    class Comment: public Statement {
    public:
        Comment(Slice<eval::Tokens> tokens);
        void lint() const override;
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<eval::Tokens> const&);
    };
}