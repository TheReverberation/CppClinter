#include <sstream>

#include "ParseFail.hpp"

using std::ostringstream;

namespace clnt::parse::err {
    ParseFail::ParseFail(clnt::Slice<vector<std::shared_ptr<eval::Token>>> tokens): _tokens(move(tokens)) {}

    char const* ParseFail::what() const noexcept {
        ostringstream ss;
        ss << "ParseFail, tokens: [";
        for (size_t i = 0; i < _tokens.size() - 1; ++i) {
            ss << *_tokens[i] << ", ";
        }
        ss << _tokens.back() << "]";
        return ss.str().data();
    }
}
