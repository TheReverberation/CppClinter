#include "Block.hpp"

#include "allFinders.hpp"

using std::vector;
using std::move;
using std::unique_ptr;
using std::make_unique;
using std::pair;
using std::string;

using namespace clnt::util;

using clnt::eval::Token;
using clnt::eval::TokenType;
using clnt::parse::Parser;
using clnt::lint::Linter;
using clnt::eval::Evaluator;

namespace {

    vector<Slice<string>> split(Slice<string> const &s, char delimiter) {
        vector<Slice<string>> result;
        size_t begin = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == delimiter) {
                result.push_back(s.slice(begin, i));
                begin = i + 1;
            }
        }
        if (begin != s.size()) {
            result.push_back(s.slice(begin));
        }
        return result;
    }

    string tabShift(string const& s) {
        string result;
        vector<Slice<string>> lines = split(makeSlice(s), '\n');
        for (auto& line : lines) {
            result += '\t';
            std::copy(line.begin(), line.end(), std::back_inserter<string>(result));
            result += '\n';
        }
        return result;
    }
}

using clnt::eval::Tokens;

namespace clnt::states {

    Block::Block(Slice<Tokens> tokens): Statement(StatementType::BLOCK, std::move(tokens)) {
    }

    pair<unique_ptr<Statement>, size_t> Block::find(Slice<Tokens> const& tokens) {
        if (tokens[0]->type == TokenType::BLOCK) {
            return {make_unique<Block>(tokens.slice(0, 1)), 1};
        }
        return {nullptr, 0};
    }

    void Block::lint() const {
        Evaluator evaluator(eval::finders::FINDERS);
        Tokens intoTokens =
                evaluator.evaluate(tokens[0]->lexemes.slice(1, tokens[0]->lexemes.size() - 1));


        Parser parser(states::STATEMENT_FINDERS);
        Slice<vector<unique_ptr<Statement>>> statements = parser.parse(move(intoTokens));


        Linter linter;
        _linted = linter.lint(statements, lint::Space::LOCAL);

        if (_linted[0] != '\n') {
            _linted = string("\n") + _linted;
        }
        if (_linted.back() != '\n') {
            _linted += '\n';
        }

        _linted = tabShift(_linted);
        _linted = (string("{") + _linted + string("}"));
    }

}
