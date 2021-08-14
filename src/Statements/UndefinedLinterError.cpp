#include "UndefinedLinterError.hpp"

namespace clnt::states::err {
    char const* UndefinedLinterError::what() const noexcept {
        return "UndefinedLinterError";
    }
}