//
// Created by dasha on 15.04.2023.
//
/*
 * TODO:
 * */

#include "RE.h"
#include <algorithm>
#include <utility>


ENFA RE::toENFA() const{
    ENFA enfa;
    enfa.setAlphabet(alfabet);
    enfa.setEpsChar(eps_char);
    if(isChar()){
        // epsilon construction for single char. return it
        enfa = enfa.symboolENFA(symbool);
    }
    else if(operation == '+'){
        ENFA up = left->toENFA();
        ENFA down = right->toENFA();
        State* begin = new State;
        State* end = new State;
        enfa.addState(begin, true, false);
        enfa.addState(end, false, true);
        enfa.addArc(begin, up.getBeginState(), eps_char);
        enfa.addArc(begin, down.getBeginState(), eps_char);
        for(auto s: up.getAcceptingStates()){
            s->setAccepting(false);
            enfa.addArc(s, end, eps_char);
        }
        for(auto s: down.getAcceptingStates()) {
            s->setAccepting(false);
            enfa.addArc(s, end, eps_char);
        }
    }
    else if(operation == '.'){
        ENFA first = left->toENFA();
        ENFA second = right->toENFA();
        State* begin = new State;
        State* end = new State;
        enfa.addState(begin, true, false);
        enfa.addState(end, false, true);
        enfa.addArc(begin, first.getBeginState(), eps_char);
        for(auto s:first.getAcceptingStates()){
            s->setAccepting(false);
            enfa.addArc(s, second.getBeginState(), eps_char);
        }
    }
    if(kleene_ster){
            ENFA to_return;
            State* begin = new State;
            State* end = new State;
            to_return.addState(begin, true, false);
            to_return.addState(end, false, true);
            to_return.addArc(begin, enfa.getBeginState(), eps_char);
            for(auto s:enfa.getAcceptingStates()){
                s->setAccepting(false);
                to_return.addArc(s, end, eps_char);
                to_return.addArc(s,enfa.getBeginState(), eps_char);
            }
            // enfa.getBeginState()->setStarting(false);
            to_return.addArc(begin, end, eps_char);
            return to_return;
    }else{
        return enfa;
    }
}
bool RE::isChar()const{
    if(symbool != '\0' && operation == '\0') return true;
    return false;
}
void RE::recursiveSplit(std::string regex){
    addLeftAndRight();
    left->eps_char = eps_char;
    right->eps_char = eps_char;
    // Recursive
    // Only one char? add it to symbool. No recursive call
    if(regex.size() == 0) return; // normaal gezien kan dat nooit
    if(regex.size() == 1){
        symbool = regex[0];
        return;
    }
    // Minstens twee chars
    // if begins with brackets
    else if(regex[0] == '('){
        unsigned int brackets_count = 1;
        for(unsigned int ind = 1; ind < regex.size(); ind++){
            if(regex[ind] == '(') brackets_count++;
            else if (regex[ind] == ')') brackets_count--;
            if(brackets_count == 0){
                left->recursiveSplit(regex.substr(1, ind-1));
                if(ind + 1 == regex.size()){
                    // There is no right regex, oeps
                }
                else if(regex[ind + 1] == '*'){
                    left->kleene_ster = true;
                    if(regex[ind+2] == '+'){
                        operation = '+';
                        right->recursiveSplit(regex.substr(ind+3));
                    }else{
                        operation = '.';
                        right->recursiveSplit(regex.substr(ind+2));
                    }
                }
                else if(regex[ind + 1] == '+'){
                    operation = '+';
                    right->recursiveSplit(regex.substr(ind+2));
                }
                else{
                    operation = '.';
                    right->recursiveSplit(regex.substr(ind+1));
                }
                break;
            }
        }
    }
    // Find first operators (for brackets).
    else{
        if (regex.size() == 2){
            // Er zijn twee mogelijkheden ab of a*
            if(regex[1] == '*'){
                symbool = regex[0];
                kleene_ster = true;
                return;
            }
            else{
                left->symbool = regex[0];
                right->symbool = regex[1];
                operation = '.';
            }
        }
        // The first char is a symbol (or a star?)
        else if(regex[1] == '+'){
            left->symbool = regex[0];
            right->recursiveSplit(regex.substr(2));
            operation = '+';
        }
        else if(regex[1] == '*'){
            left -> symbool = regex[0];
            left -> kleene_ster = true;
            if(regex[2] == '+'){
                operation = '+';
                right->recursiveSplit(regex.substr(3));
            }else{
                operation = '.';
                right->recursiveSplit(regex.substr(2));
            }
            return;
        }
        else{
            // Concatenation
            left -> symbool = regex[0];
            right->recursiveSplit(regex.substr(1));
            operation = '.';
        }
    }
}
RE::RE(std::string regex, char eps) {
    eps_char = eps;
    recursiveSplit(regex);
    parseAlfabet(regex);
}

RE::RE() {
}

void RE::addLeftAndRight(){
    left = new RE;
    right = new RE;
}

void RE::parseAlfabet(std::string regex){
    std::vector<char> ignored_chars = {eps_char, '(', ')', '*', '+'};
    for(char i: regex){
        if(std::find(ignored_chars.begin(), ignored_chars.end(), i) == ignored_chars.end()){
            alfabet.insert(i);
        }
    }
}
