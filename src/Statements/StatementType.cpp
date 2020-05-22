//
// Created by Daniil Nedaiborsch on 19.04.2020.
//

#include "StatementType.hpp"

namespace clnt::states {

    std::string TYPE_NAMES[255];

    void initTypeNames() {

        for (size_t i = 0; i < 255; ++i) {
            TYPE_NAMES[i] = "$(TypeName)";
        }

        TYPE_NAMES[(int)StatementType::BLOCK] = "Block";
        TYPE_NAMES[(int)StatementType::INSTRUCTION] = "Instruction";
        TYPE_NAMES[(int)StatementType::EXPRESSION] = "Expression";
        TYPE_NAMES[(int)StatementType::STRUCT] = "Struct";
        TYPE_NAMES[(int)StatementType::FUNCTION] = "Function";
        TYPE_NAMES[(int)StatementType::IF] = "If";
        TYPE_NAMES[(int)StatementType::ELSE] = "Else";
        TYPE_NAMES[(int)StatementType::IFELSE] = "IfElse";
        TYPE_NAMES[(int)StatementType::PREPROCESSOR] = "Preprocessor";
        TYPE_NAMES[(int)StatementType::TYPEDEF] = "Typedef";
    }

    std::ostream& operator<<(std::ostream& out, StatementType type) {
        return out << TYPE_NAMES[(int)type];
    }
}
