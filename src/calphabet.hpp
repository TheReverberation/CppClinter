#pragma once


#include <string>

#include <src/types.hpp>

#include "Slice.hpp"

namespace clnt::alphabet {
    Vector<Slice<std::string>> const& accessOperators();
    Vector<Slice<std::string>> const& callOperators();
    Vector<Slice<std::string>> const& unaryOperators();
    Vector<Slice<std::string>> const& operators();
    Vector<Slice<std::string>> const& commaOperator();
    Vector<Slice<std::string>> const& binaryOperators();
    Vector<Slice<std::string>> const& reserved();

    void init();
}
