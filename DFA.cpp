//
// Created by dasha on 02.03.2023.
//

#include "DFA.h"
#include <algorithm>
using json = nlohmann::json;

DFA::DFA(std::string filename) {
    std::ifstream input(filename);
    nlohmann::json j;
    input >> j;
    // Alfabet
    std::tuple<int,int,int> tupl;
    std::cout << std::setw(4) << j << std::endl;
    alfabet = j["alphabet"].get<std::vector<std::string> >();
    // States
    std::vector<json> json_states = j["states"].get<std::vector<json> >();
    std::map<std::string, State*> states;
    for(auto state:json_states){
        State* to_add = new State(state.at("name"), state.at("starting"), state.at("accepting"));
        all_states.push_back(to_add);
        states.insert(std::make_pair(state.at("name"), to_add));
    }
    // Transitions
    std::vector<json> json_transitions = j["transitions"].get<std::vector<json> >();
    for(auto transition:json_transitions){
        State* to_edit = states.at(transition.at("from"));
        State* to_state = states.at(transition.at("to"));
        std::string char_inp = transition["input"].get<std::string>();
        to_edit->addTransition(char_inp, to_state);
    }
    // Begin state
    for(auto state_tupple: states){
        if(state_tupple.second->isStarting()){
            begin_state = state_tupple.second;
            break;
        }
    }
}

bool DFA::accepts(std::string inp) const{
    State* current = begin_state;
    for(int i = 0; i < inp.size(); i++){
        current = current->getTransition(std::string(1, inp[i]));
    }
    //const State to_find = current;
    return current->isAccepting();
}

void DFA::print() const{
    json j;
    j["type"] = "DFA";
    j["alphabet"] = alfabet;
    j["states"] = {};
    int i = 0;
    for(State* state: all_states){
        json obj;
        obj["name"] = state->getName();
        obj["starting"] = state->isStarting();
        obj["accepting"] = state->isAccepting();
        j["states"][i] = obj;
        i++;
    }
    j["transitions"] = {};
    i = 0;
    for(State* state: all_states){
        for(auto s: alfabet){
            json obj;
            obj["from"] = state->getName();
            obj["to"] = state->getTransition(s)->getName();
            obj["input"] = s;
            j["transitions"][i] = obj;
            i++;
        }
    }
    std::cout << std::setw(4) << j << std::endl;
}

RE DFA::toRE() const {
    RE to_return;
    return to_return;
}