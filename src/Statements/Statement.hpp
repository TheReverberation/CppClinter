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
        Statement(StatementType, Slice<vector<shared_ptr<Token>>>);
        virtual ~Statement();

        StatementType const type;
        Slice<vector<shared_ptr<Token>>> const tokens;
    
        string const& linted() const;
        virtual void lint() const;
        //virtual ~Statement() = 0;
    protected:
        string mutable _linted;
    };

    std::ostream& operator<<(std::ostream& out, Statement const& s);

    // Statement finder, it's similar to LexemeFinder
    typedef pair<shared_ptr<Statement>, size_t> (*Finder)(Slice<vector<shared_ptr<Token>>> const&);
}
