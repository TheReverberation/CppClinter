#include "Parser.hpp"

#include <cassert>
#include <utility>

namespace clnt::parse {
    Parser::Parser(vector<Finder> finders): finders_(std::move(finders)) {}

    pair<Statement*, size_t> Parser::find(Slice<vector<Token*>> const& tokens) const {
        if (tokens.size() == 0) {
            return {nullptr, 0};
        }
        pair<Statement*, size_t> found = {nullptr, 0};
        for (Finder finder : finders_) {
            found = finder(tokens);
            if (found.first) {
                return found;
            }

        }
        return {nullptr, 0};
    }

    Slice<vector<Statement*>> Parser::parse(Slice<vector<Token*>> const& tokens) const {
        vector<Statement*> parsed;

        for (size_t i = 0; i < tokens.size();) {
            pair<Statement*, size_t> found = {nullptr, 0};
            for (Finder finder : finders_) {
                found = finder(tokens.slice(i));
                if (found.first) {
                    parsed.push_back(found.first);
                    i += found.second;
                    break;
                }
            }
            if (found.first == nullptr) {
                throw err::ParseFail(tokens.slice(i));
            }
        }
        return makeSlice(move(parsed));
    }
}
