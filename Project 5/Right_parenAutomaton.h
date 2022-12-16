//
// Created by jacob on 9/15/22.
//

#ifndef PROJECT1_RIGHT_PARENAUTOMATON_H
#define PROJECT1_RIGHT_PARENAUTOMATON_H

#include "Automaton.h"

class Right_parenAutomaton : public Automaton
{
public:
    Right_parenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};
#endif //PROJECT1_RIGHT_PARENAUTOMATON_H
