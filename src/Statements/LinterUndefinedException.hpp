//
// Created by Daniil Nedaiborsch on 30.04.2020.
//

#pragma once

#include <exception>

namespace clnt::states {
    class LinterUndefinedException : public std::exception {
    public:
        LinterUndefinedException();
        const char* what() const noexcept override;
    };
}


