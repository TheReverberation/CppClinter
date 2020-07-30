#include <memory>
#include <string>

#include "Typedef.hpp"

using std::move;
using std::make_shared;
using std::shared_ptr;
using std::string;

using clnt::eval::TokenType;

namespace clnt::states {
    Typedef::Typedef(clnt::Slice<vector<Token*>> tokens): Statement(StatementType::TYPEDEF, move(tokens)) {}

    pair<Statement*, size_t> Typedef::find(Slice<vector<Token*>> const& tokens) {
        if (tokens[0]->type == TokenType::RESERVED && tokens[0]->lexemes[0]->source == string("typedef")) {
            return {make_shared<Typedef>(tokens.slice(0, 1)), 1};
        } else {
            return {nullptr, 0};
        }
    }

    void Typedef::lint() const {
        _linted = "typedef";
    }

}
