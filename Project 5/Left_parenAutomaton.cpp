//
// Created by jacob on 9/15/22.
//

#include "Left_parenAutomaton.h"

void Left_parenAutomaton::S0(const std::string& input) {
    if (input[index] == '(') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}