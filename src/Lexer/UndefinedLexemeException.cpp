#include "UndefinedLexemeException.hpp"

namespace clnt::lex::err {
    UndefinedLexemeException::UndefinedLexemeException() = default;

    char const* UndefinedLexemeException::what() const noexcept {
        return "UndefinedLexemeException";
    }
}