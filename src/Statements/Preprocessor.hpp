#pragma once

#include "Statement.hpp"

namespace clnt::states {
    class Preprocessor: public Statement {
    public:
        Preprocessor(Slice<vector<Token*>>);
        static pair<Statement*, size_t> find(Slice<vector<eval::Token*>> const&);
        void lint() const override;
    };
}

