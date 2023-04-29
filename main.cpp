#include "DFA.h"

using namespace std;

int main() {

    DFA dfa("dfa3.json");
    DFA mindfa = dfa.minimize();
    dfa.printTable();

    mindfa.print();
    return 0;
}