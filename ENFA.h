//
// Created by dasha on 18.04.2023.
//

#ifndef TA_DFA_1_ENFA_H
#define TA_DFA_1_ENFA_H

#include <vector>
#include "iostream"
#include "State.h"
#include <set>
class ENFA {
private:
    std::set<char> alphabet;
    std::vector<State*> accepting_states;
    std::vector<State*> all_states;
    State* begin_state;
    char eps_char;
    std::set<State*> epsilon_closure(State* s, std::set<State*> already_evaluated);
public:
    ENFA();
    void printStats() const;
    bool accepts(const std::string& input_string) const;
    void addState(State* state, bool starting, bool accepting);
    ENFA symboolENFA(char symbool);
    void addArc(State* from_state, State* to_state, char symbol);

    const std::set<char> &getAlphabet() const;

    void setAlphabet(const std::set<char> &alphabet);

    const std::vector<State *> &getAcceptingStates() const;

    State *getBeginState() const;

    char getEpsChar() const;

    void setEpsChar(char epsChar);

    const std::vector<State *> &getAllStates() const;

    void setBeginState(State *beginState);

    std::set<State*> epsilon_closure(State*);
};


#endif //TA_DFA_1_ENFA_H
