//
// Created by jacob on 9/15/22.
//

#include "UndefinedAutomaton.h"
#include <cctype>

void UndefinedAutomaton::S0(const std::string& input) {
    if (input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
    else if (input[index] == '#') {
        inputRead++;
        index++;
        S3(input);
    }
}

void UndefinedAutomaton::S1(const std::string& input) {
    if (inputRead == static_cast<int>(input.length())){

    }
    else if(input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
   else{
       if(input[index] == '\n'){
           newLines++;
       }
       inputRead++;
       index++;
       S1(input);
   }
}

void UndefinedAutomaton::S2(const std::string& input) {
    if (input[index] == EOF){
        Serr();
    }
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else{
        Serr();
    }
}

void UndefinedAutomaton::S3(const std::string& input){
    if (input[index] == '|'){
        inputRead++;
        index++;
        S4(input);
    }
    else{
        Serr();
    }
}

void UndefinedAutomaton::S4(const std::string& input){
    if (inputRead == static_cast<int>(input.length())){

    }
    else if (input[index] == '|') {
        inputRead++;
        index++;
        S5(input);
    }
    else {
        if(input[index] == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
        S4(input);
    }
}

void UndefinedAutomaton::S5(const std::string& input){
    if (input[index] == '#'){
        Serr();
    }
    else{
        if(input[index] == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
        S4(input);
    }
}
