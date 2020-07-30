#pragma once

#include <cassert>
#include <memory>
#include <vector>
#include <utility>


#include "StatementType.hpp"
#include "UndefinedLinterError.hpp"

#include "src/Slice.hpp"
#include "src/Lexer/Lexeme.hpp"
#include "src/Evaluator/Token.hpp"

#include <src/PrimeGC.hpp>

using std::shared_ptr;
using std::string;
using std::vector;
using std::pair;

using clnt::eval::Token;

namespace clnt::states {

    /*
     * Base abstract class for all statements
     */
    class Statement {
    public:
        Statement(StatementType, Slice<vector<Token*>>);
        StatementType const type;
        Slice<vector<Token*>> const tokens;
        string const& linted() const;
        virtual void lint() const;
        virtual ~Statement();
        static mem::PrimeGC<Statement> gc;
    protected:
        string mutable _linted;
    };

    std::ostream& operator<<(std::ostream& out, Statement const& s);

    // Statement finder, it's similar to LexemeFinder
    typedef pair<Statement*, size_t> (*Finder)(Slice<vector<Token*>> const&);
}
