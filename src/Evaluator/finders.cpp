//
// Created by Daniil Nedaiborsch on 19.04.2020.
//


#include "finders.hpp"

#include <utility>
#include <memory>

using std::unique_ptr;
using std::make_unique;
using std::pair;

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::string;

using clnt::lex::Lexeme;
using clnt::lex::LexemeType;

namespace {
    pair<shared_ptr<clnt::eval::Token>, size_t> const NOTFOUND = {nullptr,0};
}

namespace clnt::eval::finders {

    unique_ptr<pair<size_t, size_t>>
    findBrackets(Slice<vector<shared_ptr<Lexeme>>> const& lexemes, vector<char> const& bracketSet) {
        if (lexemes[0]->source[0] != bracketSet[0]) {
            return nullptr;
        }
        size_t i = 1;
        int brackets = 1;
        while (i < lexemes.size() && brackets != 0) {
            if (lexemes[i]->source[0] == bracketSet[0]) {
                ++brackets;
            } else if (lexemes[i]->source[0] == bracketSet[1]) {
                --brackets;
            }
            ++i;
        }
        assert(brackets == 0);
        return make_unique<pair<size_t, size_t>>(0, i);
    }

    pair<shared_ptr<Token>, size_t> findBlock(Slice<vector<shared_ptr<Lexeme>>> const& lexemes, shared_ptr<Token> lastToken) {
        auto brackets = findBrackets(lexemes, {'{', '}'});
        if (!brackets) {
            return NOTFOUND;
        }
        return {make_shared<Token>(TokenType::BLOCK, lexemes.slice(0, brackets->second)), brackets->second};
    }

    pair<shared_ptr<Token>, size_t> findCallOperator(Slice<vector<shared_ptr<Lexeme>>> const& lexemes, shared_ptr<Token> lastToken) {
        auto brackets = findBrackets(lexemes, {'(', ')'});
        if (brackets) {
            return {make_shared<Token>(TokenType::CALL_OPERATOR, lexemes.slice(0, brackets->second)), brackets->second};
        }
        brackets = findBrackets(lexemes, {'[', ']'});
        if (brackets) {
            return {make_shared<Token>(TokenType::CALL_OPERATOR, lexemes.slice(0, brackets->second)), brackets->second};
        }
        return NOTFOUND;
    }

    pair<shared_ptr<Token>, size_t> findOperator(Slice<vector<shared_ptr<Lexeme>>> const& lexemes, shared_ptr<Token> lastToken) {
        using namespace clnt::alphabet;

        if (lexemes[0]->type != LexemeType::OPERATOR) {
            return NOTFOUND;
        }

        auto checkin = [&] (vector<Slice<string>> const& set) -> bool {
            return std::find(set.begin(), set.end(), lexemes[0]->source) != set.end();
        };

        if (lexemes[0]->source.size() == 2) {
            if (checkin(BINARY_OPERATORS)) {
                return {make_shared<Token>(TokenType::BINARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(UNARY_OPERATORS)) {
                return {make_shared<Token>(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(ACCESS_OPERATORS)) {
                return {make_shared<Token>(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            }
        } else if (lexemes[0]->source.size() == 1) {
            if (checkin(BINARY_OPERATORS) && checkin(UNARY_OPERATORS)) {
                if (lastToken != nullptr &&
                    (lastToken->type == TokenType::IDENTIFIER || lastToken->type == TokenType::CALL_OPERATOR)) {
                    return {make_shared<Token>(TokenType::BINARY_OPERATOR, lexemes.slice(0, 1)), 1};
                } else {
                    return {make_shared<Token>(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
                }
            } else if (checkin(BINARY_OPERATORS)) {
                return {make_shared<Token>(TokenType::BINARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(UNARY_OPERATORS)) {
                return {make_shared<Token>(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(ACCESS_OPERATORS)) {
                return {make_shared<Token>(TokenType::ACCESS_OPERATOR, lexemes.slice(0, 1)), 1};
            }
        }
        return NOTFOUND;
    }

    pair<shared_ptr<Token>, size_t> findReserved(Slice<vector<shared_ptr<Lexeme>>> const& lexemes, shared_ptr<Token> lastToken) {
        if (lexemes[0]->type == LexemeType::NAME) {
            return {make_shared<Token>(TokenType::RESERVED, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<shared_ptr<Token>, size_t> findSemicolon(Slice<vector<shared_ptr<Lexeme>>> const& lexemes, shared_ptr<Token> lastToken) {
        if (lexemes[0]->type == LexemeType::SEMICOLON) {
            return {make_shared<Token>(TokenType::SEMICOLON, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<shared_ptr<Token>, size_t> findWord(Slice<vector<shared_ptr<Lexeme>>> const& lexemes, shared_ptr<Token> lastToken) {
        using namespace clnt::alphabet;

        if (lexemes[0]->type == LexemeType::NAME) {
            if (std::find(RESERVED.begin(), RESERVED.end(), lexemes[0]->source) != RESERVED.end()) {
                return {make_shared<Token>(TokenType::RESERVED, lexemes.slice(0, 1)), 1};
            } else {
                return {make_shared<Token>(TokenType::IDENTIFIER, lexemes.slice(0, 1)), 1};
            }
        }
        return NOTFOUND;
    }

    pair<shared_ptr<Token>, size_t> findLineBreak(Slice<vector<shared_ptr<Lexeme>>> const& lexemes, shared_ptr<Token> lastToken) {
        if (lexemes[0]->type == LexemeType::LINE_BREAK) {
            return {make_shared<Token>(TokenType::LINE_BREAK, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<shared_ptr<Token>, size_t> findComma(Slice<vector<shared_ptr<Lexeme>>> const& lexemes, shared_ptr<Token> lastToken) {
        if (lexemes[0]->type == LexemeType::COMMA) {
            return {make_shared<Token>(TokenType::COMMA, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    vector<TokenFinder> FINDERS;

    void init() {
        FINDERS = {
                findWord, findBlock, findOperator, findCallOperator, findSemicolon, findLineBreak, findComma
        };
    }
}
