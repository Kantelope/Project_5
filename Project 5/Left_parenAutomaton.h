//
// Created by jacob on 9/15/22.
//

#ifndef PROJECT1_LEFT_PARENAUTOMATON_H
#define PROJECT1_LEFT_PARENAUTOMATON_H

#include "Automaton.h"

class Left_parenAutomaton : public Automaton
{
public:
    Left_parenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};
#endif //PROJECT1_LEFT_PARENAUTOMATON_H
