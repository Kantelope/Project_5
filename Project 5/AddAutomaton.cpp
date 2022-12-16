//
// Created by jacob on 9/15/22.
//

#include "AddAutomaton.h"

void AddAutomaton::S0(const std::string& input) {
    if (input[index] == '+') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}