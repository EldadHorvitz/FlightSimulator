//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include "PrintCommand.h"

PrintCommand::PrintCommand() {

}

int PrintCommand::execute(vector<string> v, int index,map<string, Var *> *varsMap,map<string, Var *> *simMap) {
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
//        if (varsmap.count(name)) {
//            cout << varsmap[name].getVal();
//        }
        name = "";
        if (c == '"') {
            i++;
            c = v[index + 1][i];
            while (c != '"' && c != ')') {
                name += c;
                i++;
                c = v[index + 1][i];
            }
            if (c!=')'){
                cout << name<<endl;
            }

        }
    }
    return 2;
}
