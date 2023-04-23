#include "RE.h"
#include "ENFA.h"
#include <iostream>
using namespace std;

int main() {
    RE re("(kd+x+k)(i)*(k+i)",'x');
    ENFA enfa = re.toENFA();
    enfa.printStats();

    // geven true
    cout << boolalpha << enfa.accepts("kdk") << endl;
    cout << boolalpha << enfa.accepts("i") << endl;
    cout << boolalpha << enfa.accepts("kiiiiii") << endl;

    // geven false
    cout << boolalpha << enfa.accepts("kikk") << endl;
    cout << boolalpha << enfa.accepts("") << endl;
    cout << boolalpha << enfa.accepts("kdiiiiiiki") << endl;
}

/*
 * {
    "alphabet": [
        "0",
        "1"
    ],
    "states": [
        {
            "accepting": false,
            "name": "Q0",
            "starting": true
        },
        {
            "accepting": true,
            "name": "Q1",
            "starting": false
        }
    ],
    "transitions": [
        {
            "from": "Q0",
            "input": "0",
            "to": "Q0"
        },
        {
            "from": "Q0",
            "input": "1",
            "to": "Q1"
        },
        {
            "from": "Q1",
            "input": "0",
            "to": "Q1"
        },
        {
            "from": "Q1",
            "input": "1",
            "to": "Q0"
        }
    ],
    "type": "DFA"
}
{
    "alphabet": [
        "0",
        "1"
    ],
    "type": "DFA"
}
 */