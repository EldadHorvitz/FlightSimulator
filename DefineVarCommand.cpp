//
// Created by nizan on 18/12/2019.
//

#include <iostream>
#include "DefineVarCommand.h"
#include "Var.h"

DefineVarCommand::DefineVarCommand() { }

int DefineVarCommand::execute(vector<string> v, int index,map<string, Var *> *varsMap,map<string, Var *> *simMap) {
    int i = 0;
    char c = v[index + 1][i];
    string name = "";
    double val;
    int dir=-999;
    string path = "";
    while (!isalpha(c)) {
        i++;
        c = v[index + 1][i];
    }
    while (isalpha(c)) {
        name += c;
        i++;
        c = v[index + 1][i];
    }
    if (c == ' ') {
        i++;
        c = v[index + 1][i];
    }

    if (c == '-' && v[index + 1][i + 1] == '>') {
        dir = 1;
    }
    if (c == '<' && v[index + 1][i + 1] == '-') {
        dir = 0;
    }
    while (c != '"') {
        i++;
        c = v[index + 1][i];
    }
    i++;
    c = v[index + 1][i];
    while (c != '"') {
        path += c;
        i++;
        c = v[index + 1][i];
    }
    Var* a = new Var(-999,dir,path);
    varsMap->insert({name,a});
    simMap->insert({path,a});
    return 2;

}
