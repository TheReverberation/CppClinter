#include <sstream>

#include "ParseFail.hpp"

using std::ostringstream;

using clnt::eval::Tokens;

namespace clnt::parse::err {
    ParseFail::ParseFail(Slice<Tokens> tokens) noexcept: _tokens(move(tokens)) {}

    char const* ParseFail::what() const noexcept {
        // dangerous
        ostringstream ss;
        ss << "ParseFail, tokens: [";
        for (size_t i = 0; i < _tokens.size() - 1; ++i) {
            ss << *_tokens[i] << ", ";
        }
        ss << _tokens.back() << "]";
        return ss.str().data();
    }
}
