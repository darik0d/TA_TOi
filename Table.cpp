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

Table::Table(std::vector<State*> all_states){
    // Let's collect all names and sort them
    for(State* s : all_states) states.insert(s->getName());
    // Maak een lege tabel aan
    for(int i = 1; i < states.size(); i++){
        std::vector<bool> to_push;
        for(int k = 0; k < i; k++) to_push.push_back(false);
        cells.push_back(to_push);
    }
}

void Table::print() const{
    int i = 0;
    for(auto naam:states){
        if (naam == *states.begin()) continue;
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
    for(auto naam:states){
        if (naam == *states.rbegin()) continue;
        std::cout << naam << "\t";
    }
    std::cout << std::endl;
}
bool Table::getBool(std::string A, std::string B) const{
    auto it = std::find(states.begin(), states.end(), A);
    int pos_a = std::distance(states.begin(), it);
    it = std::find(states.begin(), states.end(), B);
    int pos_b = std::distance(states.begin(), it);
    // pos_b moet groeter zijn
    if(pos_b < pos_a) std::swap(pos_a, pos_b);
    return cells[pos_b-1][pos_a];
}

Table::Table() {}

