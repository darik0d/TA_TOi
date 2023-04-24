#include "RE.h"
#include "ENFA.h"
#include <iostream>
using namespace std;

/*no_of_states=22
no_of_transitions[x]=20
no_of_transitions[d]=1
no_of_transitions[i]=2
no_of_transitions[k]=3
degree[0]=1
degree[1]=16
degree[2]=5
true
true
true
false
false
false*/
int main() {
    RE re("(kd+x+k)(i)*(k+i)",'x');
//    RE re("kd+x+k",'x');
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

//int main() {
//    RE re("(m+y)*+(e+y+m+i)s",'e');
//    ENFA enfa = re.toENFA();
//    enfa.printStats();
//
//    // geven true
//    cout << boolalpha << enfa.accepts("ys") << endl;
//    cout << boolalpha << enfa.accepts("mmyyymmmym") << endl;
//    cout << boolalpha << enfa.accepts("s") << endl;
//
//    // geven false
//    cout << boolalpha << enfa.accepts("ss") << endl;
//    cout << boolalpha << enfa.accepts("ims") << endl;
//    cout << boolalpha << enfa.accepts("mimis") << endl;
//
//    return 0;
//}

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