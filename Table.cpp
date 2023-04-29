//
// Created by dasha on 24.04.2023.
//

#include "Table.h"
#include "State.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <bits/stdc++.h>

Table::Table(const std::vector<State*>& all_states, std::set<std::string> alfab){
    // Let's collect all names and sort them
    for(State* s : all_states) states_names.insert(s->getName());
    // Maak een lege tabel aan
    for(int i = 1; i < states_names.size(); i++){
        std::vector<bool> to_push;
        for(int k = 0; k < i; k++) to_push.push_back(false);
        cells.push_back(to_push);
    }
    states = all_states;
    alfabet = alfab;
}
void Table::arrangeTable(){
    // Eerste stap van TFA
    for(auto A:states){
        for(auto B:states){
            if(A->isAccepting() && !B->isAccepting()){
                setBool(A->getName(), B->getName(), true);
            }
        }
    }
    bool final = false;
    while (!final){
            final = true;
            // Volgende stappen van TFA
            for (auto A:states){
                for (auto B: states) {
                    if(A == B) continue;
                    // Is er een kruisje?
                    if (getBool(A->getName(), B->getName())) {
                        // Ja, => zoek transities met deze combinatie
                        for (auto sym: alfabet) {
                            for (auto C: states) {
                                for (auto D: states) {
                                    if(C==D) continue;
                                    State *trans_c = C->getTransition(sym[0]);
                                    State *trans_d = D->getTransition(sym[0]);
                                    if ((trans_c == A && trans_d == B) || (trans_c == B && trans_d == A)) {
                                        // Ga na of het al staat
                                        if(getBool(C->getName(), D->getName())) continue;
                                        // Zet een kruisje
                                        setBool(C->getName(), D->getName(), true);
                                        final = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
}
void Table::print() const{
    int i = 0;
    for(auto naam:states_names){
        if (naam == *states_names.begin()) continue;
        std::cout << naam;
        for(int k = 0; k < cells[i].size(); k++) {
            std::cout << "   ";
            if(cells[i][k]) std::cout << "X";
            else std::cout << "-";
        }
        i++;
        std::cout << std::endl;
    }
    // Print the last line
    std::cout << "    ";
    for(auto naam:states_names){
        if (naam == *states_names.rbegin()) continue;
        std::cout << naam << "   ";
    }
    std::cout << std::endl;
}
bool Table::getBool(std::string A, std::string B) const{
    // TODO: of true?
    if(A == B) return true;
    auto it = std::find(states_names.begin(), states_names.end(), A);
    int pos_a = std::distance(states_names.begin(), it);
    it = std::find(states_names.begin(), states_names.end(), B);
    int pos_b = std::distance(states_names.begin(), it);
    // pos_b moet groeter zijn
    if(pos_b < pos_a) std::swap(pos_a, pos_b);
    return cells[pos_b-1][pos_a];
}
void Table::setBool(std::string A, std::string B, bool b){
    auto it = std::find(states_names.begin(), states_names.end(), A);
    int pos_a = std::distance(states_names.begin(), it);
    it = std::find(states_names.begin(), states_names.end(), B);
    int pos_b = std::distance(states_names.begin(), it);
    // pos_b moet groeter zijn
    if(pos_b < pos_a) std::swap(pos_a, pos_b);
    cells[pos_b-1][pos_a] = b;
}
std::vector<State*> Table::getEquivalentStates(State* s) const{
    std::vector<State*> to_return;
    for(const auto& B: states){
        // If there is no cross
        if(!getBool(s->getName(), B->getName())){
            to_return.push_back(B);
        }
    }
    return to_return;
}
std::vector<State*> Table::getMergedStates() const{
    std::vector<State*> to_return;
    // Get states
    for(State* s:states){
        // TODO: skip for multiple char names
        // Get all equivalent states
        std::vector<State*> equivalent_states = getEquivalentStates(s);

        // Make a new state with correct name
        std::string state_name = "{";

        // create (sorted) set with all names
        std::set<std::string > names;
        names.insert(s->getName());
        for(auto eq:equivalent_states){
            names.insert(eq->getName());
        }
        // Add all names
        for(const auto& name:names){
            state_name.append(name);
            if(name != *names.rbegin()) state_name.append(", ");
        }
        state_name.append("}");
        bool is_starting = false;
        bool is_accepting = false;
        for(auto state:equivalent_states){
            if(state->isAccepting()) is_accepting = true;
            if(state->isStarting()) is_starting = true;
        }
        if(s->isAccepting()) is_accepting = true;
        if(s->isStarting()) is_starting = true;
        State* to_add = new State(state_name, is_starting, is_accepting);
        to_return.push_back(to_add);
    }
    // Remove duplicates
    std::vector<State*> temp;
    for(State* s: to_return){
        int dubli = 0;
        for(State* added: temp){
            if(added->getName() == s->getName()) dubli++;
        }
        if(temp.empty() || dubli == 0) temp.push_back(s);
    }
    to_return = temp;
    // Set transitions
    for(State* s: to_return) {
        for (auto sym: alfabet) {
            // Get from reference
            std::string name_of_referenced_state = s->getName().substr(1, s->getName().find(',')-1);
            if(name_of_referenced_state.back() == '}') name_of_referenced_state = name_of_referenced_state.substr(0, name_of_referenced_state.size()-1);
            State *from_reference;
            for(auto ref: states){
                if(ref->getName() == name_of_referenced_state) {
                    from_reference = ref;
                    break;
                }
            }
            // Get to reference
            State *to_reference = from_reference->getTransition(sym[0]);
            // Get actual to_state
            State* to_state;
            // TODO: correct split for multiple chars
            for(auto possible_destination: to_return) if(possible_destination->getName().find(to_reference->getName()) != possible_destination->getName().npos) to_state = possible_destination;
            s->addTransition(sym[0], to_state);
        }
    }
    return  to_return;
}
Table::Table() {}

