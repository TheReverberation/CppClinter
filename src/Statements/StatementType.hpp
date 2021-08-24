#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>


namespace clnt::states {
    enum class StatementType: uint8_t {
        STRUCT, LOOP, INSTRUCTION, EXPRESSION, PREPROCESSOR, BLOCK, FUNCTION, IF, ELSE, IFELSE, TYPEDEF, CASE,
        COMMENT
    };

    void initTypeNames();
    extern std::string TYPE_NAMES[];
    std::ostream& operator<<(std::ostream& out, StatementType type);

}
