//
// Created by dasha on 18.04.2023.
//

#include "ENFA.h"

void ENFA::printStats() const{

}

bool ENFA::accepts(std::string inp) const{

}

ENFA::ENFA() {
}

void ENFA::addArc(State* from_state, State* to_state, char symbol){
    from_state->addTransition(symbol, to_state);
}