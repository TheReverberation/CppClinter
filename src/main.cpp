#include <iostream>
#include <fstream>
#include <memory>

#include <src/types.hpp>

#include "calphabet.hpp"
#include "Lexer/Lexer.hpp"
#include "Lexer/LexemeType.hpp"


#include "Evaluator/Evaluator.hpp"
#include "Evaluator/Token.hpp"
#include "Evaluator/finders.hpp"
#include "Evaluator/TokenType.hpp"
#include "Slice.hpp"

#include "Statements/all.hpp"

#include "Parser/Parser.hpp"




void init() {

    using namespace clnt;
    using namespace std;

    using clnt::states::Instruction;
    using clnt::states::Block;
    using clnt::states::Expression;
    using clnt::lint::Linter;

    alphabet::init();
    lex::finders::init();
    lex::initTypeNames();
   // states::initTypeNames();
    eval::initTypeNames();
    eval::finders::init();
    //states::arithm::initLinters();
}


int main() {
    using namespace clnt;
    using namespace std;

    using clnt::states::Instruction;
    using clnt::states::Block;
    using clnt::states::Expression;
    using clnt::lint::Linter;

    ::init();


    string inputFileName;
    cout << "Input file: ";
    cin >> inputFileName;
    ifstream fin(inputFileName);

    while (!fin.is_open()) {
        cout << "File not found!\nInput file: ";
        cin >> inputFileName;
        fin.open(inputFileName);
    }

    ofstream fout("out.c");

    lex::Lexer lexer(lex::finders::FINDERS);
    shared_ptr<string> s = make_shared<string>();

    while (fin) {
        string line;
        getline(fin, line);
        *s += line + '\n';
    }

   Vector<unique_ptr<lex::Lexeme>> lexemes = lexer.lexing(s);
    std::cout << "~MainLexemes~\n";
    for (auto& now : lexemes) {
        std::cout << *now << '\n';
    }
    std::cout << '\n';

    eval::Evaluator evaluator(eval::finders::FINDERS);
//    Vector<unique_ptr<eval::Token>> tokens = evaluator.evaluate(move(lexemes));
//
//    std::cout << "~MainTokens~\n";
//    for (auto& now : tokens) {
//        std::cout << *now << '\n';
//    }
//    std::cout << "\n";

//    parse::Parser parser(states::STATEMENT_FINDERS);
//    Slice<Vector<shared_ptr<Statement>>> states = parser.parse(tokens);
//
//    std::cout << "~MainStates~\n";
//    for (auto& now : states) {
//        std::cout << *now << '\n';
//    }
//    std::cout << '\n';
//
//    Linter linter;
//    fout << linter.lint(states, lint::Space::GLOBAL) << '\n';

    return 0;
}
