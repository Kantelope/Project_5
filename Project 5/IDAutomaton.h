//
// Created by jacob on 9/15/22.
//

#ifndef PROJECT1_IDAUTOMATON_H
#define PROJECT1_IDAUTOMATON_H

#include "Automaton.h"

class IDAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    IDAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT1_IDAUTOMATON_H
