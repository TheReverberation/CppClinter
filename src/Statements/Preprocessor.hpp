#pragma once

#include "Statement.hpp"

namespace clnt::states {
    class Preprocessor: public Statement {
    public:
        Preprocessor(Slice<NonCopyableVector<unique_ptr<Token>>>);
        static pair<unique_ptr<Statement>, size_t> find(Slice<NonCopyableVector<unique_ptr<Token>>> const&);
        void lint() const override;
    };
}

