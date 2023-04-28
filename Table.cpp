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

Table::Table(std::vector<State*> all_states, std::set<std::string> alfab){
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
            std::cout << "\t";
            if(cells[i][k]) std::cout << "X";
            else std::cout << "-";
        }
        i++;
        std::cout << std::endl;
    }
    // Print the last line
    std::cout << " \t";
    for(auto naam:states_names){
        if (naam == *states_names.rbegin()) continue;
        std::cout << naam << "\t";
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

Table::Table() {}

