/*
 * C alphabet constants
 */

#pragma once

#include <vector>
#include <string>

#include <src/util/Slice.hpp>

namespace clnt::alphabet {
    std::vector<util::Slice<std::string>> const& accessOperators();
    std::vector<util::Slice<std::string>> const& callOperators();
    std::vector<util::Slice<std::string>> const& unaryOperators();
    std::vector<util::Slice<std::string>> const& operators();
    std::vector<util::Slice<std::string>> const& commaOperator();
    std::vector<util::Slice<std::string>> const& binaryOperators();
    std::vector<util::Slice<std::string>> const& reserved();

    void init();
}
