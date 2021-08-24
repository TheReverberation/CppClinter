#include "EvaluateException.hpp"

using std::string;
using std::move;

using clnt::util::Slice;
using clnt::lex::Lexemes;

namespace clnt::eval::err {
    EvaluateException::EvaluateException(string message, Slice<Lexemes> where): message_(move(message)), where_(move(where)) {}

    char const* EvaluateException::what() const noexcept {
        return message_.c_str();
    }
}
