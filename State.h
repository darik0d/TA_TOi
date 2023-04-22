//
// Created by dasha on 02.03.2023.
//

#ifndef TA_DFA_1_STATE_H
#define TA_DFA_1_STATE_H

#include <iostream>
#include <map>

class State{
private:
    std::string name;
    bool starting;
    bool accepting;
    std::multimap<char, State*> transitions;
public:
    State();
    State(const std::string &name, bool starting, bool accepting);
    bool isStarting(){return starting;}
    bool isAccepting(){return accepting;}
    void addTransition(char sym, State*& to);
    State* getTransition(char sym);
    std::pair <std::multimap<char,State*>::iterator, std::multimap<char,State*>::iterator> getTransitions(char sym);

    const std::string &getName() const;
};


#endif //TA_DFA_1_STATE_H
