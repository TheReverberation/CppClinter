#pragma once

#include <vector>
#include <string>

#include <src/Slice.hpp>

#include "Statement.hpp"


namespace clnt::states {
    class Case: public Statement {
    public:
        Case(clnt::Slice<std::vector<std::shared_ptr<eval::Token>>>);
        void lint() const override;
        static std::pair<std::shared_ptr<Statement>, size_t> find(clnt::Slice<std::vector<std::shared_ptr<eval::Token>>> const&);
    };
}



