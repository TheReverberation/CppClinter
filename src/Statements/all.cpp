//
// Created by Daniil Nedaiborsch on 27.04.2020.
//

#include "all.hpp"

namespace clnt::states {
    std::vector<Finder> STATEMENT_FINDERS = {
            Struct::find, IfElseStatement::find, IfStatement::find, ElseStatement::find, Instruction::find, Block::find, Expression::find, 
    };
}
