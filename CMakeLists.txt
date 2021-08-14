cmake_minimum_required(VERSION 3.1)
project(CppClinter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "-Wall -g3")
set(CMAKE_BUILD_RPATH /build)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(CppClinter src/main.cpp src/Lexer/LexemeType.hpp
        src/Lexer/finders.hpp src/Lexer/finders.cpp src/calphabet.hpp src/calphabet.cpp
        src/Lexer/Lexer.cpp src/Lexer/LexemeType.cpp src/Parser/Parser.cpp src/Parser/Parser.hpp
        src/Statements/Statement.hpp src/Statements/StatementType.hpp src/Slice.hpp src/Statements/Statement.cpp
        src/Statements/Struct.cpp src/Statements/Struct.hpp src/Statements/Block.cpp src/Statements/Block.hpp
        src/Statements/StatementType.cpp
        src/Evaluator/Evaluator.cpp src/Evaluator/Evaluator.hpp
        src/Evaluator/Token.cpp src/Evaluator/Token.hpp src/Evaluator/TokenType.cpp src/Evaluator/TokenType.hpp
        src/Evaluator/finders.hpp src/Evaluator/finders.cpp src/Statements/Instruction.cpp
        src/Statements/Instruction.hpp src/Statements/Arithmetic/linters.hpp
        src/Statements/Arithmetic/linters.cpp src/Statements/Arithmetic/findCompleteExpression.hpp
        src/Statements/Arithmetic/findCompleteExpression.cpp src/Statements/all.hpp src/Statements/Expression.cpp
        src/Statements/Expression.hpp src/Linter/Linter.cpp src/Linter/Linter.hpp
        src/Evaluator/all.hpp src/Lexer/Lexeme.cpp src/Lexer/Lexeme.hpp src/Lexer/all.hpp
        src/Statements/UndefinedLinterError.cpp src/Statements/UndefinedLinterError.hpp
        src/Statements/IfStatement.hpp src/Statements/IfStatement.cpp
        src/Statements/ElseStatement.hpp src/Statements/ElseStatement.cpp
        src/Statements/IfElseStatement.hpp src/Statements/IfElseStatement.cpp src/Statements/Preprocessor.cpp
        src/Statements/Preprocessor.hpp src/Statements/Typedef.cpp src/Statements/Typedef.hpp
        src/Statements/Case.cpp src/Statements/Case.hpp src/Statements/Comment.cpp src/Statements/Comment.hpp
        src/Parser/ParseFail.hpp src/Parser/ParseFail.cpp src/Statements/Arithmetic/UndefinedLinterError.hpp
        src/Statements/Arithmetic/UndefinedLinterError.cpp src/Evaluator/Error/EvaluateException.cpp
        src/Evaluator/Error/EvaluateException.hpp src/Statements/allFinders.hpp src/Statements/allFinders.cpp code2.c)

#find_package(Boost REQUIRED COMPONENTS system)
#target_include_directories(CppClinter PUBLIC ${Boost_INCLUDE_DIRS})