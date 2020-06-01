#include "EvaluateException.hpp"

using std::string;
using std::move;

namespace clnt::eval::err {
    EvaluateException::EvaluateException(string message): message_(move(message)) {}

    char const* EvaluateException::what() const noexcept {
        return message_.c_str();
    }
}