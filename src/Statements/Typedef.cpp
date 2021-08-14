#include <memory>
#include <string>

#include "Typedef.hpp"

using std::move;
using std::make_unique;
using std::unique_ptr;
using std::string;
using std::pair;

using clnt::eval::TokenType;
using clnt::eval::Token;
using clnt::eval::Tokens;

namespace clnt::states {
    Typedef::Typedef(clnt::Slice<Tokens> tokens): Statement(StatementType::TYPEDEF, move(tokens)) {}

    pair<unique_ptr<Statement>, size_t> Typedef::find(Slice<Tokens> const& tokens) {
        if (tokens[0]->type == TokenType::RESERVED && tokens[0]->lexemes[0]->source == string("typedef")) {
            return {make_unique<Typedef>(tokens.slice(0, 1)), 1};
        } else {
            return {nullptr, 0};
        }
    }

    void Typedef::lint() const {
        _linted = "typedef";
    }
}
