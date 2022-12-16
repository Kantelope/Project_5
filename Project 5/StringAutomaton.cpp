//
// Created by jacob on 9/15/22.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (input[index] == EOF){
        Serr();
    }
    else if (input[index] != '\'') {
        if(input[index] == '\n'){
            ++newLines;
        }
        if(inputRead == static_cast<int>(input.length())){
            Serr();
        }
        inputRead++;
        index++;
        S1(input);
    }
    else if (input[index] == '\''){
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S2(const std::string& input){
    if (input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
}
