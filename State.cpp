//
// Created by dasha on 02.03.2023.
//

#include "State.h"

State::State(const std::string &name, bool starting, bool accepting) : name(name), starting(starting),
                                                                       accepting(accepting) {}

State::State() {}

void State::addTransition(char sym, State*& to){
    transitions.insert(std::make_pair(sym, to));
}

State* State::getTransition(char sym){
    if(transitions.find(sym) == transitions.end()) return nullptr;
    auto all_transitions = transitions.equal_range(sym);
    // Return only the first transition
    return all_transitions.first->second;
}
std::multimap<char, State*> State::getAllTransitions() const{
    return transitions;
}

std::pair <std::multimap<char,State*>::iterator, std::multimap<char,State*>::iterator> State::getTransitions(char sym){
    auto all_transitions = transitions.equal_range(sym);
    return all_transitions;
}

const std::string &State::getName() const {
    return name;
}

void State::setStarting(bool starting) {
    State::starting = starting;
}

void State::setAccepting(bool accepting) {
    State::accepting = accepting;
}
