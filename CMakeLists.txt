cmake_minimum_required(VERSION 3.1)
project(CppClinter LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


add_executable(CppClinter src/main.cpp src/SString.cpp src/LexemeType.hpp src/Lexeme.cpp src/Lexeme.hpp src/finders.hpp src/finders.cpp src/CAlphabet.hpp src/CAlphabet.cpp src/Lexer.cpp src/LexemeType.cpp)

find_package(Boost REQUIRED)
target_include_directories(CppClinter PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(CppClinter ${Boost_LIBS})
