//
// Created by Daniil Nedaiborsch on 30.04.2020.
//

#pragma once

#include <exception>

namespace clnt::states {
    class UndefinedLinterException : public std::exception {
    public:
        UndefinedLinterException();
        const char* what() const noexcept override;
    };
}


