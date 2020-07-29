//
// Created by Daniil Nedaiborsch on 25.04.2020.
//

#pragma once

#include <src/Evaluator/Token.hpp>
#include <src/Slice.hpp>
#include <src/types.hpp>

#include <vector>

using std::shared_ptr;
using std::unique_ptr;
using std::make_unique;
using clnt::eval::Token;
using clnt::eval::TokenType;
using clnt::Slice;

namespace clnt::states::arithm {
    size_t findCompleteExpression(Slice<NonCopyableVector<unique_ptr<Token>>> const &tokens);
}
