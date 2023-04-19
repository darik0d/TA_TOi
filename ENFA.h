//
// Created by dasha on 18.04.2023.
//

#ifndef TA_DFA_1_ENFA_H
#define TA_DFA_1_ENFA_H

#include <vector>
#include "iostream"
#include "State.h"
#include <set>
class ENFA {
private:
    std::set<char> alphabet;
    std::vector<State*> accepting_states;
    std::vector<State*> all_states;
    State* begin_state;
    void addArc(State* from_state, State* to_state, char symbol);
public:
    ENFA();

    void printStats() const;
    bool accepts(std::string input_string) const;
};


#endif //TA_DFA_1_ENFA_H
