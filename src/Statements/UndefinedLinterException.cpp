//
// Created by Daniil Nedaiborsch on 30.04.2020.
//

#include "UndefinedLinterException.hpp"

namespace clnt::states {
    UndefinedLinterException::UndefinedLinterException() {}
    char const* UndefinedLinterException::what() const noexcept {
        return "UndefinedLinterException";
    }
}