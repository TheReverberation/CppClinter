//
// Created by Daniil Nedaiborsch on 19.04.2020.
//


#include "finders.hpp"

#include <cassert>
#include <utility>
#include <memory>

using std::unique_ptr;
using std::make_unique;
using std::pair;


using std::unique_ptr;
using std::make_unique;
using std::string;

using clnt::lex::Lexeme;
using clnt::lex::LexemeType;

namespace {
    pair<unique_ptr<clnt::eval::Token>, size_t> NOTFOUND() {return {nullptr,0};}
}

namespace clnt::eval::finders {

    unique_ptr<pair<size_t, size_t>>
    findBrackets(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, NonCopyableVector<char> const& bracketSet) {
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

    pair<unique_ptr<Token>, size_t> findBlock(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const&) {
        auto brackets = findBrackets(lexemes, {'{', '}'});
        if (!brackets) {
            return NOTFOUND();
        }
        return {make_unique<Token>(TokenType::BLOCK, lexemes.slice(0, brackets->second)), brackets->second};
    }

    pair<unique_ptr<Token>, size_t> findCallOperator(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const&) {
        auto brackets = findBrackets(lexemes, {'(', ')'});
        if (brackets) {
            return {make_unique<Token>(TokenType::CALL_OPERATOR, lexemes.slice(0, brackets->second)), brackets->second};
        }
        brackets = findBrackets(lexemes, {'[', ']'});
        if (brackets) {
            return {make_unique<Token>(TokenType::CALL_OPERATOR, lexemes.slice(0, brackets->second)), brackets->second};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findOperator(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        using namespace clnt::alphabet;

        if (lexemes[0]->type != LexemeType::OPERATOR) {
            return NOTFOUND();
        }

        auto checkin = [&] (Vector<Slice<string>> const& set) -> bool {
            return std::find(set.begin(), set.end(), lexemes[0]->source) != set.end();
        };

        if (lexemes[0]->source.size() == 2) {
            if (checkin(binaryOperators())) {
                return {make_unique<Token>(TokenType::BINARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(unaryOperators())) {
                return {make_unique<Token>(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(accessOperators())) {
                return {make_unique<Token>(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            }
        } else if (lexemes[0]->source.size() == 1) {
            if (checkin(binaryOperators()) && checkin(unaryOperators())) {
                if (lastToken != nullptr &&
                    (lastToken->type == TokenType::IDENTIFIER || lastToken->type == TokenType::CALL_OPERATOR)) {
                    return {make_unique<Token>(TokenType::BINARY_OPERATOR, lexemes.slice(0, 1)), 1};
                } else {
                    return {make_unique<Token>(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
                }
            } else if (checkin(binaryOperators())) {
                return {make_unique<Token>(TokenType::BINARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(binaryOperators())) {
                return {make_unique<Token>(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(accessOperators())) {
                return {make_unique<Token>(TokenType::ACCESS_OPERATOR, lexemes.slice(0, 1)), 1};
            }
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findReserved(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::NAME) {
            return {make_unique<Token>(TokenType::RESERVED, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findSemicolon(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::SEMICOLON) {
            return {make_unique<Token>(TokenType::SEMICOLON, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findWord(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        using namespace clnt::alphabet;

        if (lexemes[0]->type == LexemeType::NAME) {
            if (std::find(reserved().begin(), reserved().end(), lexemes[0]->source) != reserved().end()) {
                return {make_unique<Token>(TokenType::RESERVED, lexemes.slice(0, 1)), 1};
            } else {
                return {make_unique<Token>(TokenType::IDENTIFIER, lexemes.slice(0, 1)), 1};
            }
        } else if (lexemes[0]->type == LexemeType::CONSTANT) {
            return {make_unique<Token>(TokenType::IDENTIFIER, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findLineBreak(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::LINE_BREAK) {
            return {make_unique<Token>(TokenType::LINE_BREAK, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findComma(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::COMMA) {
            return {make_unique<Token>(TokenType::COMMA, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findSharp(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::SHARP) {
            return {make_unique<Token>(TokenType::SHARP, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findBackslash(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::BACKSLASH) {
            return {make_unique<Token>(TokenType::BACKSLASH, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findColon(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::COLON) {
            return {make_unique<Token>(TokenType::COLON, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    pair<unique_ptr<Token>, size_t> findQuestion(Slice<NonCopyableVector<unique_ptr<Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::QUESTION) {
            return {make_unique<Token>(TokenType::QUESTION, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND();
    }

    std::pair<unique_ptr<Token>, size_t> findInit(Slice<NonCopyableVector<std::unique_ptr<lex::Lexeme>>> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lastToken && lastToken->type == TokenType::BINARY_OPERATOR) {
            auto block = findBlock(lexemes, nullptr);
            if (block.first) {
                return {make_unique<Token>(TokenType::INITIALIZER, lexemes.slice(0, block.second)), block.second};
            }
        }
        return {nullptr, 0};
    }

    Vector<TokenFinder> FINDERS;

    void init() {
        FINDERS = {
                findWord, findInit, findBlock, findOperator, findCallOperator, findSemicolon, findLineBreak, findComma,
                findBackslash, findSharp, findColon, findQuestion,
        };
    }
}
