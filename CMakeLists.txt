cmake_minimum_required(VERSION 3.1)
project(CppClinter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS -Wall)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Lexer dir
set(LEXER_SOURCES
        src/Lexer/finders.cpp
        src/Lexer/Lexeme.cpp
        src/Lexer/LexemeType.cpp
        src/Lexer/UndefinedLexemeException.cpp
        src/Lexer/Lexer.cpp)

set(LEXER_HEADERS
        src/Lexer/all.hpp
        src/Lexer/finders.hpp
        src/Lexer/Lexeme.hpp
        src/Lexer/LexemeType.hpp
        src/Lexer/Lexer.hpp)

# Evaluator dir
set(EVAL_SOURCES
        src/Evaluator/Evaluator.cpp
        src/Evaluator/finders.cpp
        src/Evaluator/Token.cpp
        src/Evaluator/TokenType.cpp
        src/Evaluator/Error/EvaluateException.cpp
)

set(EVAL_HEADERS
        src/Evaluator/Error/EvaluateException.hpp
        src/Evaluator/Evaluator.hpp
        src/Evaluator/finders.hpp
        src/Evaluator/Token.hpp
        src/Evaluator/TokenType.hpp
)

# Statements dir
set(STATE_SOURCES
        src/Statements/Arithmetic/findCompleteExpression.cpp
        src/Statements/Arithmetic/linters.cpp
        src/Statements/Arithmetic/UndefinedLinterError.cpp
        src/Statements/Block.cpp
        src/Statements/Case.cpp
        src/Statements/Comment.cpp
        src/Statements/all.cpp
        src/Statements/ElseStatement.cpp
        src/Statements/Expression.cpp
        src/Statements/IfElseStatement.cpp
        src/Statements/IfStatement.cpp
        src/Statements/Instruction.cpp
        src/Statements/LinterUndefinedException.cpp
        src/Statements/UndefinedLinterError.cpp
        src/Statements/Preprocessor.cpp
        src/Statements/Statement.cpp
        src/Statements/StatementType.cpp
        src/Statements/Struct.cpp
        src/Statements/Typedef.cpp)

set(STATE_HEADERS
        src/Statements/all.hpp
        src/Statements/Block.hpp
        src/Statements/ElseStatement.hpp
        src/Statements/Expression.hpp
        src/Statements/IfElseStatement.hpp
        src/Statements/IfStatement.hpp
        src/Statements/Instruction.hpp
        src/Statements/LinterUndefinedException.hpp
        src/Statements/Preprocessor.hpp
        src/Statements/Statement.hpp
        src/Statements/Struct.hpp
        src/Statements/Typedef.hpp)

set(PARSE_SOURCES
        src/Parser/Parser.cpp
        src/Parser/ParseFail.cpp)

set(PARSE_HEADERS
        src/Parser/Parser.hpp)

set(LINTER_SOURCES
        src/Linter/Linter.cpp
        src/Linter/)

add_executable(CppClinter
        #src/main.cpp
        #src/vector_test.cpp
        src/test_build.cpp
        src/Slice.hpp
        src/calphabet.cpp
        src/accumulate.hpp
        src/PrimeGC.hpp
        
        ${LEXER_SOURCES} ${LEXER_HEADERS}
        ${EVAL_SOURCES} ${EVAL_HEADERS}
        #${STATE_SOURCES} ${STATE_HEADERS}
        #${PARSE_SOURCES} ${PARSE_HEADERS}
        #${LINTER_SOURCES}
)

        
