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

using namespace clnt::eval;
using std::stringstream;

namespace {
    string undefinedLinter(Token* token, Token* last) {
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

    string lintArithmetic(Slice<vector<Token*>> tokens) {
        std::stringstream linted;
        Token* lastToken = nullptr;
        if (tokens.size() && tokens[0]->type == TokenType::LINE_BREAK) {
            return "\n";
        } else {

            for (auto &token : tokens) {
                // ignoring line breaks
                if (token->type == TokenType::LINE_BREAK) {
                    continue;
                }
                if (lastToken && lastToken->type == TokenType::SEMICOLON) {
                    linted << " ";
                }
                linted << lint(token, lastToken);
                //std::cout << *token << '\n';
                //std::cout << "linted: " << linted.str() << '\n';
                lastToken = token;
            }
        }
        return linted.str();
    }

    string lint(Token* token, Token* last) {
        return LINTERS[(int)token->type](token, last);
    }

    string lintSemicolon(Token* token, Token*) {
        return ";";
    }

    string lintColon(Token* token, Token*) {
        return ": ";
    }

    string lintBinaryOperator(Token* token, Token*) {
        stringstream ss;
        ss << " " << token->lexemes[0]->source << " ";
        return ss.str();
//        return (boost::format(" %s ") % token->lexemes[0]->source).str();
    }

    string lintUnaryOperator(Token* token, Token* last) {
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

    string lintAccessOperator(Token* token, Token*) {
        stringstream ss;
        ss << token->lexemes[0]->source;
        return ss.str();
    //    return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintReservedWord(Token* token, Token* last) {
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

    string lintCallOperator(Token* token, Token* last) {
        eval::Evaluator evaluator(eval::finders::FINDERS);
        Slice<vector<Token*>> evaluated = evaluator.evaluate(token->lexemes.slice(1, token->lexemes.size() - 1));
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

    string lintOperand(Token* token, Token* last) {
        stringstream ss;
        if (last && (last->type == TokenType::IDENTIFIER || last->type == TokenType::RESERVED)) {
            (ss << " " << token->lexemes[0]->source);
            return ss.str();
        }
        (ss << token->lexemes[0]->source);
        return ss.str();
        //return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintString(Token* token, Token*) {

        stringstream ss;
        ss << token->lexemes[0]->source;
        return ss.str();
        //return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintLineBreak(Token* token, Token*) {
        return "\n";
    }

    string lintComma(Token* token, Token*) {
        return ", ";
    }

    string lintSharp(Token* token, Token*) {
        return "#";
    }

    string lintBackslash(Token* token, Token*) {
        return "\\";
    }

    string lintComment(Token* token, Token*) {
        stringstream ss;
        ss << token->lexemes[0]->source;
        return ss.str();
    }

    string lintUndefined(Token* token, Token*) {
        std::stringstream ss;
        return "";
    }

    string lintInit(Token* token, Token* last) {
        eval::Evaluator evaluator(eval::finders::FINDERS);
        //std::cout << "evabegin\n";
        auto tokens = evaluator.evaluate(token->lexemes.slice(1, token->lexemes.size() - 1));
        for (auto& now : tokens) {
            //std::cout << *now << '\n';
        }
        //std::cout << "evaend\n";
        return "{" + lintArithmetic(tokens) + "}";
    }
}
