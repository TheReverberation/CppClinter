#include "UndefinedLinterError.hpp"

namespace clnt::states::err {
    UndefinedLinterError::UndefinedLinterError() {}

    char const* UndefinedLinterError::what() const noexcept {
        return "UndefinedLinterError";
    }
}