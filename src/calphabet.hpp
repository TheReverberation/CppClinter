//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#pragma once

#include <vector>
#include <string>

#include "Slice.hpp"

using std::vector;


namespace clnt::alphabet {
    extern vector<Slice<std::string>> ACCESS_OPERATORS, CALL_OPERATORS, UNARY_OPERATORS, OPERATORS,
                                        COMMA_OPERATOR;
    extern vector<Slice<std::string>> BINARY_OPERATORS;
    extern vector<Slice<std::string>> RESERVED;
    void init();
}
