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
    return transitions.at(sym);
}

const std::string &State::getName() const {
    return name;
}
