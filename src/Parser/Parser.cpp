//
// Created by Daniil Nedaiborsch on 15.04.2020.
//

#include "Parser.hpp"

namespace clnt::parse {
    Parser::Parser(vector<Finder> const& finders): finders_(finders) {}

    pair<shared_ptr<Statement>, size_t> Parser::find(Slice<vector<shared_ptr<Token>>> const& tokens) {
        pair<shared_ptr<Statement>, size_t> found = {nullptr, 0};
        for (Finder finder : finders_) {
            found = finder(tokens);
            if (found.first) {
                return found;
            }
        }
        return {nullptr, 0};
    }

    Slice<vector<shared_ptr<Statement>>> Parser::parse(Slice<vector<shared_ptr<Token>>> const& tokens) {
        vector<shared_ptr<Statement>> parsed;

        for (size_t i = 0; i < tokens.size();) {
            pair<shared_ptr<Statement>, size_t> found = {nullptr, 0};
            for (Finder finder : finders_) {
                found = finder(tokens.slice(i));
                if (found.first) {
                    parsed.push_back(found.first);
                    i += found.second;
                    break;
                }
            }
            assert(found.first);
        }
        return makeSlice(move(parsed));
    }
}