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
    std::cout << "no_of_states=" << all_states.size() << std::endl;
    std::map<char, int> transitions;
    std::map<int, int> degrees;

    // set default values (efficient, but why not?..)
    for(char c:alphabet) transitions.insert(std::make_pair(c, 0));
    transitions.insert(std::make_pair(eps_char, 0));

    // Tel het aantal transities en degrees
    for(auto s:all_states){
        // transities
        for(char c: alphabet){
            int to_add = std::distance(s->getTransitions(c).first, s->getTransitions(c).second);
            transitions.at(c) += to_add;
        }
        // degrees
        int degree = s->getAllTransitions().size();
        if(degrees.find(degree) != degrees.end()) degrees.at(degree) += 1;
        else degrees.insert(std::make_pair(degree, 1));

        transitions.at(eps_char) += std::distance(s->getTransitions(eps_char).first, s->getTransitions(eps_char).second);
    }
    // cout!
    std::cout << "no_of_transitions=[" << eps_char << "]=" << transitions.at(eps_char) << std::endl;
    for(char c: alphabet) std::cout << "no_of_transitions=[" << c << "]=" << transitions.at(c) << std::endl;
    for(auto it = degrees.begin(); it != degrees.end(); it++) std::cout << "no_of_transitions=[" << it->first << "]=" << it->second << std::endl;
}

bool ENFA::accepts(const std::string& inp) const{
    State* current = begin_state;
    for(char c: inp){

    }
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

const std::vector<State *> &ENFA::getAllStates() const {
    return all_states;
}

void ENFA::setBeginState(State *beginState) {
    begin_state = beginState;
}
