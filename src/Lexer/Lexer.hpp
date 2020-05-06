#include <vector>

#include "Lexeme.hpp"
#include "finders.hpp"



namespace clnt::lex {
    class Lexer {
    private:
        vector<finders::LexemeFinder> finders_;
    public:
        explicit Lexer(std::vector<finders::LexemeFinder>);
        vector<shared_ptr<Lexeme>> lexing(Slice<std::string> const&);
    };
}
