//
// Created by Daniil Nedaiborsch on 15.04.2020.
//

#pragma once

#include <vector>

#include "src/Statements/all.hpp"

#include "ParseFail.hpp"

using std::vector;

using clnt::states::Finder;
using clnt::states::Statement;
using clnt::states::StatementType;

namespace clnt::parse {
    class Parser {
    public:
        Parser(vector<Finder> );
        Slice<vector<Statement*>> parse(Slice<vector<Token*>> const&) const;
        pair<Statement*, size_t> find(Slice<vector<Token*>> const&) const;
    private:
        vector<Finder> finders_;
    };
}



