/*
 * This package contains all C statements.
 */

#pragma once

#include "Statement.hpp"
#include "StatementType.hpp"
#include "Instruction.hpp"
#include "Struct.hpp"
#include "Block.hpp"
#include "Expression.hpp"
#include "IfStatement.hpp"
#include "ElseStatement.hpp"
#include "IfElseStatement.hpp"
#include "Preprocessor.hpp"
#include "Typedef.hpp"
#include "Case.hpp"
#include "Comment.hpp"

#include "Arithmetic/linters.hpp"

#include <vector>
namespace clnt::states {
    // all statement finders
    extern std::vector<Finder> STATEMENT_FINDERS;
}
