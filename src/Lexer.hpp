#include <vector>

#include "Lexeme.hpp"
#include "SString.hpp"
#include "finders.hpp"


using std::vector;

namespace clnt {
    class Lexer {
    private:
        vector<finders::Finder> finders_;
    public:
        Lexer(vector<finders::Finder>);
        vector<shared_ptr<Lexeme>> lexing(SString const&);
    };
}
