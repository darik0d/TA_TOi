//
// Created by dasha on 02.03.2023.
//

#include "State.h"

State::State(const std::string &name, bool starting, bool accepting) : name(name), starting(starting),
                                                                       accepting(accepting) {}

State::State() {}

void State::addTransition(std::string sym, State*& to){
    transitions.insert(std::make_pair(sym, to));
}

State* State::getTransition(std::string sym){
    return transitions.at(sym);
}

const std::string &State::getName() const {
    return name;
}
