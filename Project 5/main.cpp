#include "Lexer.h"
#include "DatalogProgram.h"
#include "Database.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Command line args bad" << endl;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    string input;
    //using iterators I am copying everything from the instream into the a string
    istreambuf_iterator<char> inputIt(in), emptyInputIt;
    back_insert_iterator<string> stringInsert(input);
    copy(inputIt, emptyInputIt, stringInsert);

    //intializing a new lexer object and using the run method to tokenize my input string
    Lexer* lexer = new Lexer();
    lexer->Run(input);
    //using a to_string method from lexer to output everything
    //cout << lexer->to_string();
    DatalogProgram dp(lexer->getTokens());
    dp.ParseDatalogProgram();
    Database db(dp.returnSchemes(),dp.returnFacts(),dp.returnQueries(),dp.returnRules());
    db.fill();
    cout << db.quickRules();

    cout << db.evaluate();
    delete lexer;
    return 0;
}