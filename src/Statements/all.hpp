//
// Created by Daniil Nedaiborsch on 27.04.2020.
//

#include "Statement.hpp"
#include "StatementType.hpp"
#include "Instruction.hpp"
#include "Struct.hpp"
#include "Block.hpp"
#include "Expression.hpp"
#include "IfStatement.hpp"
#include "ElseStatement.hpp"
#include "IfElseStatement.hpp"

#include "Arithmetic/linters.hpp"

#include <vector>
namespace clnt::states {
    extern std::vector<Finder> STATEMENT_FINDERS;
}