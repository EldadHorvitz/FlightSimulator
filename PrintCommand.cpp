//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include "PrintCommand.h"

PrintCommand::PrintCommand() {

}

int PrintCommand::execute(vector<string> v, int index) {
    int i = 0;
    char c = v[index + 1][i];
    string name = "";
    double val;
    while (c!=')') {
        while (c != '"' && c != ')') {
            name += c;
            i++;
            c = v[index + 1][i];
        }
        if (varsmap.count(name)) {
            cout << varsmap[name].getVal();
        }
        if (c == '"') {
            i++;
            c = v[index + 1][i];
            while (c != '"' && c != ')') {
                cout << c;
                i++;
                c = v[index + 1][i];
            }
            cout << "\n";
        }
    }
    return 2;
}
