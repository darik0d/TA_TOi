//
// Created by dasha on 15.04.2023.
//
// TODO:
// 

#include "RE.h"
#include <algorithm>
#include <utility>


ENFA RE::toENFA() const{
    if(isChar()){
        // epsilon construction for single char. return it
        ENFA to_return;
        return to_return;
    }
    else if(kleene_ster){
        // kleene ster construction. return it with recursion
    }
    else if(operation == '+'){
        // plus construction with recursion
    }
    else if(operation == '.'){
        // . construction with recursion
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
