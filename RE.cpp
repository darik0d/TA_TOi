//
// Created by dasha on 15.04.2023.
//

#include "RE.h"

#include <utility>

void RE::print() const {
    std::cout << "fg*" << std::endl;
}

ENFA RE::toENFA() const{

}
void RE::recursiveSplit(std::string regex){
    addLeftAndRight();
    // TODO: star symbol
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
                else if(regex[ind + 1] == '+'){
                    operation = '+';
                    right->recursiveSplit(regex.substr(ind+2));
                }
                // We skippen voorlopig geval *
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
                // TODO
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
            // ???
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
    recursiveSplit(std::move(regex));
    // Parse alphabet
}

RE::RE() {
}

void RE::addLeftAndRight(){
    left = new RE;
    right = new RE;
}
