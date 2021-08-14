#pragma once

#include <algorithm>
#include <vector>
#include <string>

#include "src/Slice.hpp"
#include "src/accumulate.hpp"
#include "src/Parser/Parser.hpp"

namespace clnt::lint {

    enum class Space: uint8_t {
        GLOBAL, LOCAL
    };

    class Linter {
    public:
        Linter() = default;
        std::string lint(Slice<parse::Statements> const&, Space);
    private:
    };
}


