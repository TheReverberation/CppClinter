#pragma once

#include <exception>
#include <string>

namespace clnt::eval::err {
    class EvaluateException: public std::exception {
    public:
        EvaluateException(std::string message);
        char const* what() const noexcept override;
    private:
        std::string message_;
    };
}
