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
    std::map<std::string, State*> transitions;
public:
    State();
    State(const std::string &name, bool starting, bool accepting);
    bool isStarting(){return starting;}
    bool isAccepting(){return accepting;}
    void addTransition(std::string sym, State*& to);
    State* getTransition(std::string sym);

    const std::string &getName() const;
};


#endif //TA_DFA_1_STATE_H
