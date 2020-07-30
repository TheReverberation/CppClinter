//
// Created by Daniil Nedaiborsch on 25.04.2020.
//

#pragma once

#include "src/Evaluator/Token.hpp"
#include "src/Slice.hpp"

#include <vector>

using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::make_unique;
using clnt::eval::Token;
using clnt::eval::TokenType;
using clnt::Slice;

namespace clnt::states::arithm {
    size_t findCompleteExpression(Slice<vector<shared_ptr<Token>>> const &tokens);
}
