#include <iostream>
#include <fstream>

#include <memory>

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
    states::initTypeNames();
    eval::initTypeNames();
    eval::finders::init();
    states::arithm::initLinters();
}


int main() {
    using namespace clnt;
    using namespace std;

    using clnt::states::Instruction;
    using clnt::states::Block;
    using clnt::states::Expression;
    using clnt::lint::Linter;

    ::init();

    ifstream fin("code.c");
    ofstream fout("out.c");

    lex::Lexer lexer(lex::finders::FINDERS);
    shared_ptr<string> s = make_shared<string>();

    while (fin) {
        string line;
        getline(fin, line);
        *s += line + '\n';
    }

    vector<shared_ptr<lex::Lexeme>> lexemes = lexer.lexing(s);
    std::cout << "~MainLexemes~\n";
    for (auto& now : lexemes) {
        std::cout << *now << '\n';
    }
    std::cout << '\n';

    eval::Evaluator evaluator(eval::finders::FINDERS);
    vector<shared_ptr<eval::Token>> tokens = evaluator.evaluate(lexemes);

    //auto str = states::Struct::find(tokens).first;
    //cout << "MAINSTRUCT: " << *str << '\n';
    //str->lint();
    //cout << str->linted() << '\n';


    std::cout << "~MainTokens~\n";
    for (auto now : tokens) {
        std::cout << *now << '\n';
    }
    std::cout << "\n";
/*    auto ifelsest = std::dynamic_pointer_cast<states::IfElseStatement>(states::IfElseStatement::find(tokens).first);
    std::cout << "IFFFFFFFFF\n";
    std::cout << *ifelsest->ifStatement << '\n';
    std::cout << *ifelsest->elseStatement << '\n';
    std::cout << '\n';*/
    parse::Parser parser(states::STATEMENT_FINDERS);
    Slice<vector<shared_ptr<Statement>>> states = parser.parse(tokens);
    std::cout << "~MainStates~\n";
    for (auto& now : states) {
        std::cout << *now << '\n';
    }
    std::cout << '\n';

    Linter linter;
    fout << linter.lint(states, lint::Space::GLOBAL) << '\n';

    return 0;
}
