//
// Created by Daniil Nedaiborsch on 15.04.2020.
//

#pragma once

#include <vector>

#include "src/Statements/Statement.hpp"
#include "ParseFail.hpp"



namespace clnt::parse {

    using Statements = std::vector<std::unique_ptr<states::Statement>>;

    class Parser {
    public:
        explicit Parser(std::vector<states::Finder>);
        Statements parse(Slice<eval::Tokens> const&) const;
        std::pair<std::unique_ptr<states::Statement>, size_t> find(Slice<eval::Tokens> const&) const;
    private:
        std::vector<states::Finder> const finders_;
    };
}



