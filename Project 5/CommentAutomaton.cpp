//
// Created by jacob on 9/15/22.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|'){
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] != EOF && input[index] != '\n') {
        inputRead++;
        index++;
        S3(input);
    }
}

void CommentAutomaton::S2(const std::string& input){
    if (inputRead == static_cast<int>(input.length())){
        Serr();
    }
    else if (input[index] != '|'){
        if(input[index] == '\n'){
            ++newLines;
        }
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] == '|'){
        inputRead++;
        index++;
        S4(input);
    }
}

void CommentAutomaton::S3(const std::string& input){
    if (input[index] != EOF && input[index] != '\n'){
        inputRead++;
        index++;
        S3(input);
    }
}

void CommentAutomaton::S4(const std::string& input){
    if (input[index] == '#'){
        inputRead++;
    }
    else{
        S2(input);
    }
}