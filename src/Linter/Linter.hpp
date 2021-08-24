#pragma once

#include <algorithm>
#include <vector>
#include <string>

#include <src/util/Slice.hpp>
#include <src/Parser/Parser.hpp>

namespace clnt::lint {

    enum class Space: uint8_t {
        GLOBAL, LOCAL
    };

    class Linter {
    public:
        Linter() = default;
        std::string lint(util::Slice<parse::Statements> const&, Space);
    private:
    };
}


