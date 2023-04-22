//
// Created by dasha on 18.04.2023.
//

#include "ENFA.h"

void ENFA::printStats() const{
/*no_of_states=26
no_of_transitions[e]=26
no_of_transitions[i]=1
no_of_transitions[m]=2
no_of_transitions[s]=1
no_of_transitions[y]=2
degree[0]=1
degree[1]=18
degree[2]=7*/
}

bool ENFA::accepts(std::string inp) const{

}

ENFA::ENFA() {
}

void ENFA::addArc(State* from_state, State* to_state, char symbol){
    from_state->addTransition(symbol, to_state);
}