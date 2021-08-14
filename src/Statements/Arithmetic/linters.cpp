//
// Created by Daniil Nedaiborsch on 21.04.2020.
//

#include <sstream>

#include <src/Evaluator/Evaluator.hpp>
#include <src/Lexer/Lexer.hpp>
#include <src/Parser/Parser.hpp>
#include <src/Evaluator/TokenType.hpp>

#include "linters.hpp"
#include "UndefinedLinterError.hpp"

using std::string;
using std::stringstream;
using std::unique_ptr;
using std::make_unique;

using clnt::eval::Token;
using clnt::eval::TokenType;
using clnt::eval::Tokens;

namespace {
    string undefinedLinter(unique_ptr<Token> const& token, unique_ptr<Token> const& last) {
        throw clnt::states::arithm::err::UndefinedLinterError();
    }
}

namespace clnt::states::arithm {
    Linter LINTERS[255];


    void initLinters() {

        for (size_t i = 0; i < 255; ++i) {
            LINTERS[i] = ::undefinedLinter;
        }

        LINTERS[(int)TokenType::BINARY_OPERATOR] = lintBinaryOperator;
        LINTERS[(int)TokenType::UNARY_OPERATOR] = lintUnaryOperator;
        LINTERS[(int)TokenType::ACCESS_OPERATOR] = lintAccessOperator;
        LINTERS[(int)TokenType::CALL_OPERATOR] = lintCallOperator;
        LINTERS[(int)TokenType::IDENTIFIER] = lintOperand;
        LINTERS[(int)TokenType::SEMICOLON] = lintSemicolon;
        LINTERS[(int)TokenType::RESERVED] = lintReservedWord;
        LINTERS[(int)TokenType::COMMA] = lintComma;
        LINTERS[(int)TokenType::LINE_BREAK] = lintLineBreak;
        LINTERS[(int)TokenType::BACKSLASH] = lintBackslash;
        LINTERS[(int)TokenType::SHARP] = lintSharp;
        LINTERS[(int)TokenType::COLON] = lintColon;
        LINTERS[(int)TokenType::INITIALIZER] = lintInit;
        LINTERS[(int)TokenType::COMMENT] = lintComment;
    }

    string lintArithmetic(Slice<Tokens> const& tokens) {
        std::stringstream linted;
        if (tokens.size() && tokens[0]->type == TokenType::LINE_BREAK) {
            return "\n";
        } else {
            for (size_t i = 0; i < tokens.size(); ++i) {
                auto& token = tokens[i];
                auto lastToken = [&i, &tokens] () -> unique_ptr<Token> const& {
                    static unique_ptr<Token> const nulluptr = nullptr;
                    if (i > 0) {
                        return tokens[i];
                    } else {
                        return nulluptr;
                    }
                };
                // ignoring line breaks
                if (token->type == TokenType::LINE_BREAK) {
                    continue;
                }
                if (lastToken() && lastToken()->type == TokenType::SEMICOLON) {
                    linted << " ";
                }
                linted << lint(token, lastToken());
                //std::cout << *token << '\n';
                //std::cout << "linted: " << linted.str() << '\n';

            }
        }
        return linted.str();
    }

    string lint(unique_ptr<Token> const& token, unique_ptr<Token> const& last) {
        return LINTERS[(int)token->type](token, last);
    }

    string lintSemicolon(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        return ";";
    }

    string lintColon(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        return ": ";
    }

    string lintBinaryOperator(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        stringstream ss;
        ss << " " << token->lexemes[0]->source << " ";
        return ss.str();
//        return (boost::format(" %s ") % token->lexemes[0]->source).str();
    }

    string lintUnaryOperator(unique_ptr<Token> const& token, unique_ptr<Token> const& last) {
        if (token->lexemes[0]->source[0] == ',') {
            return ", ";
        }
        stringstream ss;
        if (token->lexemes[0]->source[0] == '&' || token->lexemes[0]->source[0] == '*') {
            ss << token->lexemes[0]->source;
            return ss.str();
//            return (boost::format("%s") % token->lexemes[0]->source).str();
        }
        ss << token->lexemes[0]->source;
        return ss.str();
  //      return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintAccessOperator(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        stringstream ss;
        ss << token->lexemes[0]->source;
        return ss.str();
    //    return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintReservedWord(unique_ptr<Token> const& token, unique_ptr<Token> const& last) {
        stringstream ss;
        if (last && (last->type == TokenType::IDENTIFIER || last->type == TokenType::RESERVED)) {
            ss << " " << token->lexemes[0]->source;
            return ss.str();
      //      return (boost::format(" %s") % token->lexemes[0]->source).str();
        }
        ss << token->lexemes[0]->source;
        return ss.str();
        //return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintCallOperator(unique_ptr<Token> const& token, unique_ptr<Token> const& last) {
        eval::Evaluator evaluator(eval::finders::FINDERS);
        Slice<Tokens> evaluated = evaluator.evaluate(token->lexemes.slice(1, token->lexemes.size() - 1));
        string linted = lintArithmetic(evaluated);
        stringstream ss;
        if (last && last->type == TokenType::RESERVED) {
            ss << " " << token->lexemes[0]->source << linted <<
                    token->lexemes[token->lexemes.size() - 1]->source;
            return ss.str();
        } else {
            ss << token->lexemes[0]->source << linted <<
                    token->lexemes[token->lexemes.size() - 1]->source;
            return ss.str();
        }
    }

    string lintOperand(unique_ptr<Token> const& token, unique_ptr<Token> const& last) {
        stringstream ss;
        if (last && (last->type == TokenType::IDENTIFIER || last->type == TokenType::RESERVED)) {
            (ss << " " << token->lexemes[0]->source);
            return ss.str();
        }
        (ss << token->lexemes[0]->source);
        return ss.str();
        //return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintString(unique_ptr<Token> const& token, unique_ptr<Token> const&) {

        stringstream ss;
        ss << token->lexemes[0]->source;
        return ss.str();
        //return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintLineBreak(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        return "\n";
    }

    string lintComma(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        return ", ";
    }

    string lintSharp(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        return "#";
    }

    string lintBackslash(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        return "\\";
    }

    string lintComment(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        stringstream ss;
        ss << token->lexemes[0]->source;
        return ss.str();
    }

    string lintUndefined(unique_ptr<Token> const& token, unique_ptr<Token> const&) {
        std::stringstream ss;
        return "";
    }

    string lintInit(unique_ptr<Token> const& token, unique_ptr<Token> const& last) {
        eval::Evaluator evaluator(eval::finders::FINDERS);
        //std::cout << "evabegin\n";
        auto tokens = evaluator.evaluate(token->lexemes.slice(1, token->lexemes.size() - 1));
        for (auto& now : tokens) {
            //std::cout << *now << '\n';
        }
        //std::cout << "evaend\n";
        return "{" + lintArithmetic(move(tokens)) + "}";
    }
}
