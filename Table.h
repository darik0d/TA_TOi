//
// Created by dasha on 24.04.2023.
//

#ifndef TA_DFA_1_TABLE_H
#define TA_DFA_1_TABLE_H
#include <iostream>
#include <vector>
#include <set>

class State;
class Table {
    std::vector<std::vector<bool> > cells;
    std::set<std::string > states;
public:
    Table();

    Table(std::vector<State*> all_states);
    void print() const;
    bool getBool(std::string A, std::string B) const;
};


#endif //TA_DFA_1_TABLE_H
