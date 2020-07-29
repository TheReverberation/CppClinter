#include <vector>
#include <memory>

#include <src/types.hpp>

#include "Lexeme.hpp"
#include "finders.hpp"


namespace clnt::lex {
    class Lexer {
    private:
        NonCopyableVector<finders::LexemeFinder> finders_;
    public:
        explicit Lexer(NonCopyableVector<finders::LexemeFinder>);
        NonCopyableVector<std::unique_ptr<Lexeme>> lexing(Slice<std::string> const&);
    };
}
