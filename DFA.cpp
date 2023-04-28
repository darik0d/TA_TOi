//
// Created by dasha on 02.03.2023.
//

#include "DFA.h"
#include <algorithm>
using json = nlohmann::json;
#include "Table.h"

DFA::DFA(std::string filename) {
    std::ifstream input(filename);
    nlohmann::json j;
    input >> j;
    // Alfabet
    std::tuple<int,int,int> tupl;
    // std::cout << std::setw(4) << j << std::endl;
    alfabet = j["alphabet"].get<std::set<std::string> >();
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
        char char_inp = transition["input"].get<std::string>()[0];
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
        current = current->getTransition(inp[i]);
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
            // make char from string
            obj["to"] = state->getTransition(s[0])->getName();
            obj["input"] = s;
            j["transitions"][i] = obj;
            i++;
        }
    }
    std::cout << std::setw(4) << j << std::endl;
}

DFA DFA::minimize() {
    DFA to_return;
    table = Table(all_states, alfabet);
    // TF algo
    table.arrangeTable();
    // Now we have to build DFA with given info
    to_return.alfabet = alfabet;
    to_return.all_states = table.getMergedStates();
    for(auto s: to_return.all_states){
        if(s->isStarting()) to_return.begin_state = s;
        if(s->isAccepting()) to_return.accepting_states.push_back(s);
    }
    return to_return;
}

void DFA::printTable() const{
    table.print();
}

DFA::DFA() {}

bool DFA::operator==(DFA dfa)const{
    return true;
}
