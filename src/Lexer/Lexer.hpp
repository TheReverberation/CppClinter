#include <vector>
#include <memory>

#include "Lexeme.hpp"
#include "finders.hpp"


namespace clnt::lex {
    class Lexer {
    private:
        std::vector<finders::LexemeFinder> finders_;
    public:
        explicit Lexer(std::vector<finders::LexemeFinder>);
        std::vector<std::shared_ptr<Lexeme>> lexing(Slice<std::string> const&);
    };
}
