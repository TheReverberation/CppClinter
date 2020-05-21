#pragma once

#include "Statement.hpp"

namespace clnt::states {
    class Preprocessor: public Statement {
    public:
        Preprocessor(Slice<vector<shared_ptr<Token>>>);
        static pair<shared_ptr<Statement>, size_t> find(Slice<vector<shared_ptr<Token>>> const&);
        void lint() const override;
    };
}

