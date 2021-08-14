#include "Comment.hpp"

#include <algorithm>
#include <iterator>

using std::unique_ptr;
using std::make_unique;
using std::pair;
using std::make_pair;
using std::copy;
using std::back_inserter;
using std::vector;

using clnt::eval::Token;
using clnt::eval::TokenType;
using clnt::eval::Tokens;

namespace clnt::states {
    Comment::Comment(Slice<Tokens> tokens):
        Statement(StatementType::COMMENT, move(tokens)) {}

    pair<unique_ptr<Statement>, size_t> Comment::find(Slice<Tokens> const& tokens) {
        if (tokens[0]->type == TokenType::COMMENT) {
            return {make_unique<Comment>(tokens.slice(0, 1)), 1};
        }
        return {nullptr, 0};
    }

    void Comment::lint() const {
        copy(tokens[0]->lexemes[0]->source.begin(), tokens[0]->lexemes[0]->source.end(),
                back_inserter(_linted));
    }
}

