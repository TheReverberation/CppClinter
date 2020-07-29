//
// Created by Daniil Nedaiborsch on 15.04.2020.
//

#pragma once

#include <vector>

#include "src/Statements/all.hpp"

using std::vector;

using clnt::states::Finder;
using clnt::states::Statement;
using clnt::states::StatementType;

namespace clnt::parse {
    class Parser {
    public:
        Parser(vector<Finder> );
        Slice<vector<shared_ptr<Statement>>> parse(Slice<vector<shared_ptr<Token>>> const&);
        pair<shared_ptr<Statement>, size_t> find(Slice<vector<shared_ptr<Token>>> const&);
    private:
        vector<Finder> finders_;
    };
}



