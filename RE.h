//
// Created by dasha on 15.04.2023.
//

#ifndef TA_DFA_1_RE_H
#define TA_DFA_1_RE_H
#include <iostream>
#include "ENFA.h"

class RE {
private:
    RE* left;
    RE* right;
    char operation;
    char symbool = '\0';
    std::vector<std::string> alfabet;
    char eps_char;
    void recursiveSplit(std::string regex);
    void addLeftAndRight();
public:
    RE();

    RE(std::string regex, char eps_char);

    void print() const;
    ENFA toENFA() const;
};


#endif //TA_DFA_1_RE_H
