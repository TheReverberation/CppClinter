#pragma once

#include "Statement.hpp"

namespace clnt::states {
    class Preprocessor: public Statement {
    public:
        explicit Preprocessor(Slice<eval::Tokens>);
        static std::pair<std::unique_ptr<Statement>, size_t> find(Slice<eval::Tokens> const&);
        void lint() const override;
    };
}

