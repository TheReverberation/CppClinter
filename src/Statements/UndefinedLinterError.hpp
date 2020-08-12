//
// Created by Daniil Nedaiborsch on 30.04.2020.
//

#pragma once

#include <exception>

namespace clnt::states::err {
    class UndefinedLinterError: public std::exception {
    public:
        UndefinedLinterError();
        const char* what() const noexcept override;
    };
}


