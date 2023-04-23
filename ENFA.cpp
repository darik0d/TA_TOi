//
// Created by dasha on 18.04.2023.
//

#include "ENFA.h"

std::set<State*> ENFA::epsilon_closure(State* s, std::set<State*> already_evaluated)const{
    std::set<State*> to_return;
    to_return.insert(s);
    already_evaluated.insert(s);
    // Pak eps closure van 1 stap eps transities
    auto to_evaluate = s->getTransitions(eps_char);
    for(auto it = to_evaluate.first; it != to_evaluate.second; it++){
        if(to_return.find(it->second) != to_return.end() || already_evaluated.find(it->second) != already_evaluated.end()) continue;
        std::set<State*> e_closure = epsilon_closure(it->second, already_evaluated);
        // What to do with this closure? Insert!
        for(auto state:e_closure){
            to_return.insert(state);
        }
    }
    return to_return;
}
std::set<State*> ENFA::epsilon_closure(State* s) const{
    std::set<State*> to_return;
    std::set<State*> already_evaluated;
    to_return.insert(s);
    already_evaluated.insert(s);
    // Pak eps closure van 1 stap eps transities
    auto to_evaluate = s->getTransitions(eps_char);
    for(auto it = to_evaluate.first; it != to_evaluate.second; it++){
        if(to_return.find(it->second) != to_return.end() || already_evaluated.find(it->second) != already_evaluated.end()) continue;
        std::set<State*> e_closure = epsilon_closure(it->second, already_evaluated);
        // What to do with this closure? Insert!
        for(auto state:e_closure){
            to_return.insert(state);
        }
    }
    return to_return;
}

void ENFA::printStats() const{

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
    State* current_state = begin_state;
    // Verzamel eclosure
    auto eclosure = epsilon_closure(current_state);
    for(char c: inp){
        std::set<State*> next_states;
        // Maak een stap met gegeven staten;
        for(State* s:eclosure){
            auto to_add = s->getTransitions(c);
            for(auto it = to_add.first; it != to_add.second; it++) next_states.insert(it->second);
        }
        // Als er geen stappen zijn, return false;
        if(next_states.empty()) return false;
        eclosure.clear();
        for(State*s: next_states){
            auto to_add = epsilon_closure(s);
            eclosure.insert(to_add.begin(), to_add.end());
        }
    }
//    // Check if state is accepting or not
    for(State* s:eclosure) {
        if(s->isAccepting()) return true;
    }
    return false;
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
    to_return.setEpsChar(eps_char);
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
