#include <iostream>

#include <memory>

#include "CAlphabet.hpp"
#include "SString.hpp"
#include "Lexer.hpp"
#include "LexemeType.hpp"
#include "Lexeme.hpp"


using namespace clnt;
using namespace std;

int main() {
    alphabet::init();
    finders::init();
    initTypeNames();

    std::cout << Lexeme(make_shared<string>("asdasd"), LexemeType::SEMICOLON) << '\n';

    Lexer lexer(finders::finders);
    shared_ptr<string> s = make_shared<string>();
    getline(cin, *s);
    for (auto& lex : lexer.lexing(s)) {
        std::cout << *lex << '\n';
    }
    return 0;
}
