#include "finders.hpp"

#include <cassert>
#include <utility>
#include <memory>
#include <src/Evaluator/Error/EvaluateException.hpp>

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
    pair<clnt::eval::Token*, size_t> const NOTFOUND = {nullptr,0};
}

namespace clnt::eval::finders {

    unique_ptr<pair<size_t, size_t>>
    findBrackets(Slice<vector<Lexeme*>> const& lexemes, vector<char> const& bracketSet) {
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
        if (brackets != 0) {
            throw err::EvaluateException("Uncorrected brackets");
        }
        return make_unique<pair<size_t, size_t>>(0, i);
    }

    pair<Token*, size_t> findBlock(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        auto brackets = findBrackets(lexemes, {'{', '}'});
        if (!brackets) {
            return NOTFOUND;
        }
        return {new Token(TokenType::BLOCK, lexemes.slice(0, brackets->second)), brackets->second};
    }

    pair<Token*, size_t> findCallOperator(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        auto brackets = findBrackets(lexemes, {'(', ')'});
        if (brackets) {
            return {new Token(TokenType::CALL_OPERATOR, lexemes.slice(0, brackets->second)), brackets->second};
        }
        brackets = findBrackets(lexemes, {'[', ']'});
        if (brackets) {
            return {new Token(TokenType::CALL_OPERATOR, lexemes.slice(0, brackets->second)), brackets->second};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findOperator(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        using namespace clnt::alphabet;

        if (lexemes[0]->type != LexemeType::OPERATOR) {
            return NOTFOUND;
        }

        auto checkin = [&] (vector<Slice<string>> const& set) -> bool {
            return std::find(set.begin(), set.end(), lexemes[0]->source) != set.end();
        };

        if (lexemes[0]->source.size() == 2) {
            if (checkin(binaryOperators())) {
                return {new Token(TokenType::BINARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(unaryOperators())) {
                return {new Token(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(accessOperators())) {
                return {new Token(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            }
        } else if (lexemes[0]->source.size() == 1) {
            if (checkin(binaryOperators()) && checkin(unaryOperators())) {
                if (lastToken != nullptr &&
                    (lastToken->type == TokenType::IDENTIFIER || lastToken->type == TokenType::CALL_OPERATOR)) {
                    return {new Token(TokenType::BINARY_OPERATOR, lexemes.slice(0, 1)), 1};
                } else {
                    return {new Token(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
                }
            } else if (checkin(binaryOperators())) {
                return {new Token(TokenType::BINARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(binaryOperators())) {
                return {new Token(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(accessOperators())) {
                return {new Token(TokenType::ACCESS_OPERATOR, lexemes.slice(0, 1)), 1};
            }
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findReserved(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lexemes[0]->type == LexemeType::NAME) {
            return {new Token(TokenType::RESERVED, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findSemicolon(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lexemes[0]->type == LexemeType::SEMICOLON) {
            return {new Token(TokenType::SEMICOLON, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findWord(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        using namespace clnt::alphabet;

        if (lexemes[0]->type == LexemeType::NAME) {
            if (std::find(reserved().begin(), reserved().end(), lexemes[0]->source) != reserved().end()) {
                return {new Token(TokenType::RESERVED, lexemes.slice(0, 1)), 1};
            } else {
                return {new Token(TokenType::IDENTIFIER, lexemes.slice(0, 1)), 1};
            }
        } else if (lexemes[0]->type == LexemeType::CONSTANT) {
            return {new Token(TokenType::IDENTIFIER, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findLineBreak(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lexemes[0]->type == LexemeType::LINE_BREAK) {
            return {new Token(TokenType::LINE_BREAK, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findComma(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lexemes[0]->type == LexemeType::COMMA) {
            return {new Token(TokenType::COMMA, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findSharp(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lexemes[0]->type == LexemeType::SHARP) {
            return {new Token(TokenType::SHARP, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findBackslash(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lexemes[0]->type == LexemeType::BACKSLASH) {
            return {new Token(TokenType::BACKSLASH, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findColon(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lexemes[0]->type == LexemeType::COLON) {
            return {new Token(TokenType::COLON, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findQuestion(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lexemes[0]->type == LexemeType::QUESTION) {
            return {new Token(TokenType::QUESTION, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    pair<Token*, size_t> findComment(Slice<vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lexemes[0]->type == LexemeType::COMMENT) {
            return {new Token(TokenType::COMMENT, lexemes.slice(0, 1)), 1};
        }
        return NOTFOUND;
    }

    std::pair<Token*, size_t> findInit(Slice<std::vector<Lexeme*>> const& lexemes, Token* lastToken) {
        if (lastToken && lastToken->type == TokenType::BINARY_OPERATOR) {
            auto block = findBlock(lexemes, nullptr);
            if (block.first) {
                return {new Token(TokenType::INITIALIZER, lexemes.slice(0, block.second)), block.second};
            }
        }
        return {nullptr, 0};
    }

    vector<TokenFinder> FINDERS;

    void init() {
        FINDERS = {
                findWord, findInit, findBlock, findOperator, findCallOperator, findSemicolon, findLineBreak, findComma,
                findBackslash, findSharp, findColon, findQuestion, findComment,
        };
    }
}
