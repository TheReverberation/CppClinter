#pragma once

#include <vector>
#include <string>

#include "Slice.hpp"

namespace clnt::alphabet {
    std::vector<Slice<std::string>> const& accessOperators();
    std::vector<Slice<std::string>> const& callOperators();
    std::vector<Slice<std::string>> const& unaryOperators();
    std::vector<Slice<std::string>> const& operators();
    std::vector<Slice<std::string>> const& commaOperator();
    std::vector<Slice<std::string>> const& binaryOperators();
    std::vector<Slice<std::string>> const& reserved();

    void init();
}
