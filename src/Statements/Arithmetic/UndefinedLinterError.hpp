#pragma once

#include <exception>

namespace clnt::states::arithm::err {
    class UndefinedLinterError: public std::exception {
    public:
        char const* what() const noexcept override;
    };
}
