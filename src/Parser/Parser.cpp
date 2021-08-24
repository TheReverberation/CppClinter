#include "Parser.hpp"

#include <cassert>
#include <utility>

using std::move;
using std::pair;
using std::unique_ptr;
using std::make_unique;
using std::vector;

using namespace clnt::states;
using namespace clnt::eval;

using clnt::util::Slice;
using clnt::util::makeSlice;

namespace clnt::parse {
    Parser::Parser(vector<Finder> finders): finders_(move(finders)) {}

    pair<unique_ptr<Statement>, size_t> Parser::find(Slice<Tokens> const& tokens) const {
        if (tokens.size() == 0) {
            return {nullptr, 0};
        }
        pair<unique_ptr<Statement>, size_t> found = {nullptr, 0};
        for (Finder finder : finders_) {
            found = finder(tokens);
            if (found.first) {
                return found;
            }
        }
        return {nullptr, 0};
    }

    Statements Parser::parse(Slice<Tokens> const& tokens) const {
        vector<unique_ptr<Statement>> parsed;

        for (size_t i = 0; i < tokens.size();) {
            bool foundFlag = false;
            pair<unique_ptr<Statement>, size_t> found = {nullptr, 0};
            for (Finder finder : finders_) {
                found = finder(tokens.slice(i));
                if (found.first) {
                    parsed.push_back(move(found.first));
                    i += found.second;
                    foundFlag = true;
                    break;
                }
            }
            if (!foundFlag) {
                throw err::ParseFail(tokens.slice(i));
            }
        }
        return parsed;
    }
}
