//
// Created by dasha on 15.04.2023.
//

#ifndef TA_DFA_1_RE_H
#define TA_DFA_1_RE_H
#include <iostream>
#include "ENFA.h"
#include <set>

class RE {
private:
    RE* left;
    RE* right;
    char operation = '\0';
    char symbool = '\0';
    std::set<char> alfabet;
    bool kleene_ster = false;
    char eps_char;
    void recursiveSplit(std::string regex);
    void addLeftAndRight();
    bool isChar()const;
public:
    RE();
    RE(std::string regex, char eps_char);
    ENFA toENFA() const;
    void parseAlfabet(std::string regex);
};


#endif //TA_DFA_1_RE_H
