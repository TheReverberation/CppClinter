#pragma once

#include <exception>
#include <vector>
#include <string>

#include <src/Slice.hpp>
#include <src/Evaluator/Token.hpp>

namespace clnt::parse::err {
    class ParseFail: public std::exception {
    public:
        ParseFail(Slice<std::vector<std::shared_ptr<eval::Token>>>);
        char const* what() const noexcept override;
    private:
        std::string mutable _whatstr;
        Slice<std::vector<std::shared_ptr<eval::Token>>> _tokens;
    };
}
