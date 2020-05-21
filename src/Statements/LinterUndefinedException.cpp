//
// Created by Daniil Nedaiborsch on 30.04.2020.
//

#include "LinterUndefinedException.hpp"

namespace clnt::states {
    LinterUndefinedException::LinterUndefinedException() {}
    char const* LinterUndefinedException::what() const noexcept {
        return "LinterUndefinedException";
    }
}