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
void ENFA::addState(State* state, bool starting, bool accepting){
    all_states.push_back(state);
    if(starting) {
        begin_state = state;
        state->setStarting(true);
    }else{
        state->setStarting(false);
    }
    if(accepting) {
        accepting_states.push_back(state);
        state->setAccepting(true);
    }else{
        state->setAccepting(false);
    }
}
ENFA ENFA::symboolENFA(char symbool){
    ENFA to_return;
    State* begin = new State;
    State* end = new State;
    begin->addTransition(symbool, end);
    to_return.addState(begin, true, false);
    to_return.addState(end, false, true);
    return to_return;
}

State *ENFA::getBeginState() const {
    return begin_state;
}

const std::vector<State *> &ENFA::getAcceptingStates() const {
    return accepting_states;
}

const std::set<char> &ENFA::getAlphabet() const {
    return alphabet;
}

void ENFA::setAlphabet(const std::set<char> &alphabet) {
    ENFA::alphabet = alphabet;
}

char ENFA::getEpsChar() const {
    return eps_char;
}

void ENFA::setEpsChar(char epsChar) {
    eps_char = epsChar;
}
