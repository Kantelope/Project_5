#include "Lexer.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_markAutomaton.h"
#include "Left_parenAutomaton.h"
#include "Right_parenAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "UndefinedAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    size_t autoL = automata.size();
    size_t tokenL = tokens.size();
    for (size_t i = 0; i < autoL; i++){
        delete automata.at(i);
    }
    for (size_t i = 0; i < tokenL; i++){
        delete tokens.at(i);
    }
}
std::string Lexer::to_string(){ //error here
    std::ostringstream os;
    size_t tokL = tokens.size();
    for(size_t i = 0; i < tokL; i++){
        os << tokens.at(i)->to_string() << std::endl;
    }
    os << "Total Tokens = " << tokens.size();
    return os.str();
}

void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_markAutomaton());
    automata.push_back(new Left_parenAutomaton());
    automata.push_back(new Right_parenAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new UndefinedAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    int lineNumber = 1;
    int maxRead;
    size_t automataL = automata.size();
    while(input.size() > 0){
        maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);
        if (isblank(input[0])){
            input.erase(0,1);
            continue;
        }
        else if (input[0]== '\n'){
            lineNumber++;
            input.erase(0,1);
            continue;
        }
        else if (input[0] == EOF){
            tokens.push_back(new Token(TokenType::EF,"EOF",lineNumber));
            input.erase(0,1);
        }
        for (size_t i = 0; i < automataL; i++){
            int inputRead = automata.at(i)->Start(input);
            if (inputRead > maxRead){
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }
        if (maxRead > 0){
            Token* newToken = maxAutomaton->CreateToken(input.substr(0,maxRead),lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else{
            maxRead = 1;
            Token* newToken = UndefinedAutomaton().CreateToken(input.substr(0,1),lineNumber);
            tokens.push_back(newToken);
        }
        input.erase(0,maxRead);
    }
    Token* newToken = new Token(TokenType::EF,"",lineNumber);
    tokens.push_back(newToken);
}

std::vector<Token*> Lexer::getTokens(){
    std::vector<Token*> newTokens;
    for(size_t i = 0; i < tokens.size();i++){
        if(tokens[i]->getType() != TokenType::COMMENT){
            newTokens.push_back(tokens.at(i));
        }
    }
    return newTokens;
}
