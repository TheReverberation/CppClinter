#pragma once

#include <exception>
#include <string>

#include <src/util/Slice.hpp>

namespace clnt::lex::err {
    class UndefinedLexemeException: public std::exception {
    public:
        explicit UndefinedLexemeException(util::Slice<std::string> code);

        util::Slice<std::string> const code;
        char const* what() const noexcept override;
    };
}
