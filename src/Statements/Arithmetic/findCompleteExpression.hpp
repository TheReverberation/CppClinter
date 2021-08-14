//
// Created by Daniil Nedaiborsch on 25.04.2020.
//

#pragma once

#include "src/Evaluator/Token.hpp"
#include "src/Evaluator/Evaluator.hpp"
#include "src/Slice.hpp"

#include <vector>

namespace clnt::states::arithm {
    size_t findCompleteExpression(Slice<eval::Tokens> const &tokens);
}
