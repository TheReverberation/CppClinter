#pragma once

#include "Statement.hpp"

namespace clnt::states {
    class Preprocessor: public Statement {
    public:
        explicit Preprocessor(util::Slice<eval::Tokens>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(util::Slice<eval::Tokens> const&);
        void lint() const override;
    };
}

