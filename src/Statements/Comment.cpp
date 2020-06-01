#include "Comment.hpp"

#include <algorithm>
#include <iterator>

using std::shared_ptr;
using std::make_shared;
using std::pair;
using std::make_pair;
using std::copy;
using std::back_inserter;

using clnt::eval::Token;
using clnt::eval::TokenType;

namespace clnt::states {
    Comment::Comment(Slice<vector<std::shared_ptr<eval::Token>>> tokens):
        Statement(StatementType::COMMENT, move(tokens)) {}

    pair<shared_ptr<Statement>, size_t> Comment::find(Slice<vector<shared_ptr<Token>>> const& tokens) {
        if (tokens[0]->type == TokenType::COMMENT) {
            return {make_shared<Comment>(tokens.slice(0, 1)), 1};
        }
        return {nullptr, 0};
    }

    void Comment::lint() const {
        copy(tokens[0]->lexemes[0]->source.begin(), tokens[0]->lexemes[0]->source.end(),
                back_inserter(_linted));
    }
}

