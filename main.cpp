#include "RE.h"
#include "ENFA.h"
#include <iostream>
using namespace std;

int main() {
    RE re("(m+y)*+(e+y+m+i)s*",'e');
//    ENFA enfa = re.toENFA();
//    enfa.printStats();
//    // geven true
//    cout << boolalpha << enfa.accepts("ys") << endl;
//    cout << boolalpha << enfa.accepts("mmyyymmmym") << endl;
//    cout << boolalpha << enfa.accepts("s") << endl;
//
//    // geven false
//    cout << boolalpha << enfa.accepts("ss") << endl;
//    cout << boolalpha << enfa.accepts("ims") << endl;
//    cout << boolalpha << enfa.accepts("mimis") << endl;

    return 0;
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