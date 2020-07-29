//
// Created by Daniil Nedaiborsch on 27.04.2020.
//


#pragma once

#include <algorithm>
#include <vector>
#include <string>

#include "src/Statements/all.hpp"
#include "src/Slice.hpp"
#include <src/accumulate.hpp>

namespace clnt::lint {

    enum class Space: uint8_t {
        GLOBAL, LOCAL
    };

    class Linter {
    public:
        Linter();
        std::string lint(Slice<NonCopyableVector<std::unique_ptr<states::Statement>>> const&, Space);
    private:
    };


}


