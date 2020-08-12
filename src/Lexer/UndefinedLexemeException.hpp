#pragma once

#include <exception>

namespace clnt::lex::err {
    class UndefinedLexemeException: public std::exception {
    public:
        UndefinedLexemeException();
        char const* what() const noexcept override;
    };
}