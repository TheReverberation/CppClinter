//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#pragma once

#include <vector>

#include "SString.hpp"

using std::vector;


namespace clnt::alphabet {
    extern vector<SString> BINARY_OPERATORS, UNARY_OPERATORS, OPERATORS;
    void init();
}
