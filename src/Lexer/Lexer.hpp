#include <vector>
#include <memory>

#include <src/types.hpp>

#include "Lexeme.hpp"
#include "finders.hpp"


namespace clnt::lex {
    class Lexer {
    private:
        Vector<finders::LexemeFinder> finders_;
    public:
        explicit Lexer(Vector<finders::LexemeFinder>);
        Vector<std::unique_ptr<Lexeme>> lexing(Slice<std::string> const&);
    };
}
