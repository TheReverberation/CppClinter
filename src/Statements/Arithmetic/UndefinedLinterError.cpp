#include "UndefinedLinterError.hpp"

namespace clnt::states::arithm::err {
    UndefinedLinterError::UndefinedLinterError() {}

    char const* UndefinedLinterError::what() const noexcept {
        return "UndefinedLinterError";
    }
}
