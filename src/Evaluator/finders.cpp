#include "finders.hpp"

#include <cassert>
#include <memory>
#include <optional>
#include <utility>

#include "Error/EvaluateException.hpp"

using std::unique_ptr;
using std::make_unique;
using std::pair;

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::string;
using std::optional;
using std::nullopt;
using std::pair;
using std::make_pair;

using clnt::lex::Lexeme;
using clnt::lex::LexemeType;
using clnt::lex::Lexemes;
using clnt::util::Slice;
using clnt::util::makeSlice;

namespace {
    clnt::eval::finders::FoundToken notfound() { return {nullptr,0}; };
}

namespace clnt::eval::finders {

    optional<pair<size_t, size_t>>
    findBrackets(Slice<Lexemes> const& lexemes, vector<char> const& bracketSet) {
        if (lexemes[0]->source[0] != bracketSet[0]) {
            return nullopt;
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
            throw err::EvaluateException("Uncorrected brackets", lexemes);
        }
        return make_pair(0, i);
    }

    FoundToken findBlock(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        auto brackets = findBrackets(lexemes, {'{', '}'});
        if (!brackets) {
            return notfound();
        }
        return {make_unique<Token>(TokenType::BLOCK, lexemes.slice(0, brackets->second)), brackets->second};
    }

    FoundToken findCallOperator(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        auto brackets = findBrackets(lexemes, {'(', ')'});
        if (brackets) {
            return {make_unique<Token>(TokenType::CALL_OPERATOR, lexemes.slice(0, brackets->second)), brackets->second};
        }
        brackets = findBrackets(lexemes, {'[', ']'});
        if (brackets) {
            return {make_unique<Token>(TokenType::CALL_OPERATOR, lexemes.slice(0, brackets->second)), brackets->second};
        }
        return notfound();
    }

    FoundToken findOperator(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        using namespace clnt::alphabet;

        if (lexemes[0]->type != LexemeType::OPERATOR) {
            return notfound();
        }

        auto checkin = [&] (vector<Slice<string>> const& set) -> bool {
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
            } else if (checkin(unaryOperators())) {
                return {make_unique<Token>(TokenType::UNARY_OPERATOR, lexemes.slice(0, 1)), 1};
            } else if (checkin(accessOperators())) {
                return {make_unique<Token>(TokenType::ACCESS_OPERATOR, lexemes.slice(0, 1)), 1};
            }
        }
        return notfound();
    }

    FoundToken findReserved(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::NAME) {
            return {make_unique<Token>(TokenType::RESERVED, lexemes.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundToken findSemicolon(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::SEMICOLON) {
            return {make_unique<Token>(TokenType::SEMICOLON, lexemes.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundToken findWord(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
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
        return notfound();
    }

    FoundToken findLineBreak(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::LINE_BREAK) {
            return {make_unique<Token>(TokenType::LINE_BREAK, lexemes.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundToken findComma(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::COMMA) {
            return {make_unique<Token>(TokenType::COMMA, lexemes.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundToken findSharp(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::SHARP) {
            return {make_unique<Token>(TokenType::SHARP, lexemes.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundToken findBackslash(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::BACKSLASH) {
            return {make_unique<Token>(TokenType::BACKSLASH, lexemes.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundToken findColon(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::COLON) {
            return {make_unique<Token>(TokenType::COLON, lexemes.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundToken findQuestion(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::QUESTION) {
            return {make_unique<Token>(TokenType::QUESTION, lexemes.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundToken findComment(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lexemes[0]->type == LexemeType::COMMENT) {
            return {make_unique<Token>(TokenType::COMMENT, lexemes.slice(0, 1)), 1};
        }
        return notfound();
    }

    FoundToken findInitializer(Slice<Lexemes> const& lexemes, unique_ptr<Token> const& lastToken) {
        if (lastToken && lastToken->type == TokenType::BINARY_OPERATOR) {
            auto block = findBlock(lexemes, nullptr);
            if (block.first) {
                return {make_unique<Token>(TokenType::INITIALIZER, lexemes.slice(0, block.second)), block.second};
            }
        }
        return {nullptr, 0};
    }

    vector<TokenFinder> FINDERS;

    void init() {
        FINDERS = {
                findWord, findInitializer, findBlock, findOperator, findCallOperator, findSemicolon, findLineBreak, findComma,
                findBackslash, findSharp, findColon, findQuestion, findComment,
        };
    }
}
