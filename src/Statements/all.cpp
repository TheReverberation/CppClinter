#include "all.hpp"

namespace clnt::states {
    // emplace finders by priority descending order
    std::vector<Finder> STATEMENT_FINDERS = {
            Preprocessor::find, Struct::find, Typedef::find, IfElseStatement::find, IfStatement::find,
            ElseStatement::find, Case::find, Comment::find, Instruction::find, Block::find, Expression::find,
    };
}
