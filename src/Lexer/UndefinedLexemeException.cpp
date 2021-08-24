#include "UndefinedLexemeException.hpp"

using std::string;
using std::move;

using clnt::util::Slice;

namespace clnt::lex::err {
    UndefinedLexemeException::UndefinedLexemeException(Slice<string> code): code(move(code))
    {};

    char const* UndefinedLexemeException::what() const noexcept {
        return "UndefinedLexemeException";
    }
}
