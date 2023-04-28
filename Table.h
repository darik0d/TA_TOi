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
    std::set<std::string> alfabet;
    std::vector<std::vector<bool> > cells;
    std::set<std::string > states_names;
    std::vector<State*> states;
public:
    Table();
    void setBool(std::string A, std::string B, bool b);
    Table(const std::vector<State*>& all_states, std::set<std::string> alfab);
    void print() const;
    bool getBool(std::string A, std::string B) const;
    void arrangeTable();
    std::vector<State*> getMergedStates() const;
    std::vector<State*> getEquivalentStates(State* s) const;
};


#endif //TA_DFA_1_TABLE_H
