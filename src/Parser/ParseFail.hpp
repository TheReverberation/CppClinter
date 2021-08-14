#pragma once

#include <exception>
#include <vector>

#include "src/Slice.hpp"
#include "src/Evaluator/Token.hpp"
#include "src/Evaluator/Evaluator.hpp"

namespace clnt::parse::err {
    class ParseFail: public std::exception {
    public:
        ParseFail(Slice<eval::Tokens>) noexcept;
        char const* what() const noexcept override;
    private:
        Slice<eval::Tokens> _tokens;
    };
}
