#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <iterator>

#include "calphabet.hpp"
#include "Lexer/Lexer.hpp"
#include "Lexer/LexemeType.hpp"


#include "Evaluator/Evaluator.hpp"
#include "Evaluator/Token.hpp"
#include "Evaluator/finders.hpp"
#include "Evaluator/TokenType.hpp"
#include "Evaluator/Error/EvaluateException.hpp"

#include "src/util/Slice.hpp"

#include "Statements/all.hpp"

#include "Parser/Parser.hpp"
#include "Parser/ParseFail.hpp"

using std::stringstream;
using std::string;
using std::shared_ptr;

string outNameFile(string inputFileName) {
    using std::find;
    using std::copy;
    using std::back_inserter;
    using std::string;

    using clnt::util::Slice;

    Slice<string> s(move(inputFileName));
    size_t dot = find(s.begin(), s.end(), '.') - s.begin();
    string preffix;
    copy(s.begin(), s.begin() + dot, back_inserter(preffix));
    string result = preffix + "_linted";
    copy(s.begin() + dot, s.end(), back_inserter(result));
    return result;
}


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


int main(int argc, char** argv) {
    using namespace clnt;
    using namespace std;

    using clnt::states::Instruction;
    using clnt::states::Block;
    using clnt::states::Expression;
    using clnt::lint::Linter;
    using clnt::util::Slice;
    using clnt::util::makeSlice;
    ::init();


    string inputFileName;
    ifstream fin;
    if (argc == 1) {
        std::cout << "Input file name: ";
        std::cin >> inputFileName;
        fin.open(inputFileName);
        while (!fin.is_open()) {
            std::cout << "File not exist! Input file name: ";
            std::cin >> inputFileName;
            fin.open(inputFileName);
        } 
    } else {
        inputFileName = argv[1];
        fin.open(inputFileName);
    }

    if (!fin.is_open()) {
        cout << "File not found!\nInput file: ";
        exit(1);
    }

    ofstream fout(::outNameFile(inputFileName));

    lex::Lexer lexer(lex::finders::FINDERS);

    auto& log = std::cout;

    // read code
    string s;
    std::ifstream file(inputFileName);
    std::ostringstream oss;
    oss << file.rdbuf();
    s = oss.str();
    log << "\'" << s << "\'\n";

    auto lexemes = lexer.lexing(std::move(s));
    log << "~MainLexemes~\n";
    for (auto& now : lexemes) {
        log << *now << '\n';
    }
    log << '\n';
    
    eval::Evaluator evaluator(eval::finders::FINDERS);
    eval::Tokens tokens;
    try {
        tokens = evaluator.evaluate(move(lexemes));
    } catch (eval::err::EvaluateException const& exc) {
        std::cout << exc.what() << '\n';
        exit(1);
    }
    
    for (auto& token : tokens) {
        if (token == nullptr) {
            exit(228);
        }
    }
    log << "~MainTokens~\n";
    for (auto& now : tokens) {
        log << *now << '\n';
    }
    log << "\n";
   /* auto [state, _] = states::IfStatement::find(move(tokens)); 
    auto ifstate = unique_ptr<states::IfStatement>((states::IfStatement*)state.release());
    if (ifstate) {
        std::cout << *ifstate << '\n';
        for (auto& now : ifstate->statements) {
            std::cout << *now << '\n';
        }
    }
    ifstate->lint();
    std::cout << ifstate->linted() << '\n';*/ 
    parse::Parser parser(states::STATEMENT_FINDERS);
    try {
        Slice<parse::Statements> states = parser.parse(move(tokens));

        log << "~MainStates~\n";
        for (auto &now : states) {
            log << *now << '\n';
        }
        log << '\n';

        Linter linter;
        fout << linter.lint(states, lint::Space::GLOBAL) << '\n';
    } catch (parse::err::ParseFail const& exc) {
        std::cout << exc.what() << '\n';
        exit(1);
    }
    return 0;
}
