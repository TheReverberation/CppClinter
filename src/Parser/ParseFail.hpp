#pragma once

#include <exception>
#include <vector>

#include <src/Slice.hpp>
#include <src/Evaluator/Token.hpp>

namespace clnt::parse::err {
    class ParseFail: public std::exception {
    public:
        ParseFail(Slice<std::vector<std::shared_ptr<eval::Token>>>);
        char const* what() const noexcept override;
    private:
        Slice<std::vector<std::shared_ptr<eval::Token>>> _tokens;
    };
}
