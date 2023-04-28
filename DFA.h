//
// Created by dasha on 02.03.2023.
//

#ifndef TA_DFA_1_DFA_H
#define TA_DFA_1_DFA_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "State.h"
#include <tr1/tuple>
#include <iomanip>
#include "json.hpp"
#include <set>
#include "Table.h"
class DFA {
private:
    std::set<std::string> alfabet;
    // State: <input_symb, output_state>
    std::vector<State*> accepting_states;
    std::vector<State*> all_states;
    State* begin_state;
    Table table;
public:
    DFA();
    bool operator==(DFA dfa)const;
    explicit DFA(std::string filename);
    bool accepts(std::string inp) const;
    void print() const;
    DFA minimize();
    void printTable() const;
};


#endif //TA_DFA_1_DFA_H
