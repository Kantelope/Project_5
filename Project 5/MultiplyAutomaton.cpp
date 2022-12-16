//
// Created by jacob on 9/15/22.
//

#include "MultiplyAutomaton.h"

void MultiplyAutomaton::S0(const std::string& input) {
    if (input[index] == '*') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}