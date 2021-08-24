#pragma once

#include <src/Evaluator/Evaluator.hpp>
#include <src/util/Slice.hpp>


namespace clnt::states::arithm {
    size_t findCompleteExpression(util::Slice<eval::Tokens> const &tokens);
}
