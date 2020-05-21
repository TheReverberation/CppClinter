//
// Created by Daniil Nedaiborsch on 21.04.2020.
//

#include <sstream>
#include <src/Evaluator/Evaluator.hpp>
#include "linters.hpp"
#include "src/Evaluator/TokenType.hpp"

using namespace clnt::eval;
using std::stringstream;

namespace {
    string undefinedLinter(shared_ptr<Token> token, shared_ptr<Token> last) {
        std::cout << "Undefined linter for: " << token->type << '\n';
        exit(13);
    }
}

namespace clnt::states::arithm {

    Slice<vector<shared_ptr<Token>>> findCompleteExpression(Slice<vector<shared_ptr<Token>>> const&);


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
    }



    string lintArithmetic(Slice<vector<shared_ptr<Token>>> tokens) {
        std::stringstream linted;
        shared_ptr<Token> lastToken = nullptr;
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
                std::cout << *token << '\n';
                std::cout << "linted: " << linted.str() << '\n';
                lastToken = token;
            }
        }
        return linted.str();
    }

    string lint(shared_ptr<Token> token, shared_ptr<Token> last) {
        return LINTERS[(int)token->type](token, last);
    }

    string lintSemicolon(shared_ptr<Token> token, shared_ptr<Token>) {
        return ";";
    }

    string lintBinaryOperator(shared_ptr<Token> token, shared_ptr<Token>) {
        stringstream ss;
        ss << " " << token->lexemes[0]->source << " ";
        return ss.str();
//        return (boost::format(" %s ") % token->lexemes[0]->source).str();
    }

    string lintUnaryOperator(shared_ptr<Token> token, shared_ptr<Token> last) {
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

    string lintAccessOperator(shared_ptr<Token> token, shared_ptr<Token>) {
        stringstream ss;
        ss << token->lexemes[0]->source;
        return ss.str();
    //    return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintReservedWord(shared_ptr<Token> token, shared_ptr<Token> last) {
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

    string lintCallOperator(shared_ptr<Token> token, shared_ptr<Token> last) {
        eval::Evaluator evaluator(eval::finders::FINDERS);
        Slice<vector<shared_ptr<Token>>> evaluated = evaluator.evaluate(token->lexemes.slice(1, token->lexemes.size() - 1));
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

    string lintOperand(shared_ptr<Token> token, shared_ptr<Token> last) {
        stringstream ss;
        if (last && (last->type == TokenType::IDENTIFIER || last->type == TokenType::RESERVED)) {
            (ss << " " << token->lexemes[0]->source);
            return ss.str();
        }
        (ss << token->lexemes[0]->source);
        return ss.str();
        //return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintString(shared_ptr<Token> token, shared_ptr<Token>) {

        stringstream ss;
        ss << token->lexemes[0]->source;
        return ss.str();
        //return (boost::format("%s") % token->lexemes[0]->source).str();
    }

    string lintLineBreak(shared_ptr<Token> token, shared_ptr<Token>) {
        return "\n";
    }

    string lintComma(shared_ptr<Token> token, shared_ptr<Token>) {
        return ", ";
    }

    string lintSharp(shared_ptr<Token> token, shared_ptr<Token>) {
        return "#";
    }

    string lintBackslash(shared_ptr<Token> token, shared_ptr<Token>) {
        return "\\";
    }

    string lintUndefined(shared_ptr<Token> token, shared_ptr<Token>) {
        std::stringstream ss;
        return "";
    }
}
