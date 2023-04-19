//
// Created by dasha on 18.04.2023.
//

#ifndef TA_DFA_1_ENFA_H
#define TA_DFA_1_ENFA_H

#include <vector>
#include "iostream"
#include "State.h"

class ENFA {
private:
    std::vector<std::string> alfabet;
    std::vector<State*> accepting_states;
    std::vector<State*> all_states;
    State* begin_state;
public:
    ENFA();

    void printStats() const;
    bool accepts(std::string inp) const;
};


#endif //TA_DFA_1_ENFA_H
