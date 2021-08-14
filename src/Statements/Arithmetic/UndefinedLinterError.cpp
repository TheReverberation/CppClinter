#include "UndefinedLinterError.hpp"

namespace clnt::states::arithm::err {

    char const* UndefinedLinterError::what() const noexcept {
        return "UndefinedLinterError";
    }
}
