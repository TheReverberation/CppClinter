#pragma once

#include <exception>
#include <string>

#include <src/util/Slice.hpp>
#include <src/Lexer/Lexer.hpp>

namespace clnt::eval::err {
    class EvaluateException: public std::exception {
    public:
        EvaluateException(std::string message, util::Slice<lex::Lexemes> where);
        char const* what() const noexcept override;
    private:
        util::Slice<lex::Lexemes> where_;
        std::string message_;
    };
}
