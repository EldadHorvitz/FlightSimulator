//
// Created by nizan on 18/12/2019.
//

#include <iostream>
#include "DefineVarCommand.h"
#include "Var.h"

DefineVarCommand::DefineVarCommand() {}

//excuting the DeifneVar command by inserting the new var to the symbol table maps
int DefineVarCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    int i = 0;
    char c = v[index + 1][i];
    string name = "";
    //direction- if it needs to send the data to the simulator
    int dir = -999;
    string path = "";
    while (!isalpha(c)) {
        i++;
        c = v[index + 1][i];
    }
    while (isalpha(c) || isdigit(c)) {
        name += c;
        i++;
        c = v[index + 1][i];
    }
    if (c == ' ') {
        i++;
        c = v[index + 1][i];
    }
    //if it just needs to be initalzed by a value
    if (c == '=') {
        //assignment command
        vector<string> tempV;
        tempV.insert(tempV.begin(), name);
        tempV.insert(tempV.begin() + 1, v[index + 1].substr(i, v[index + 1].length() - 1));
        Command *ca = new AssignmentCommand();
        if (ca != NULL) {
            ca->execute(tempV, 0, varsMap, simMap);
        }
        delete ca;
        ca = nullptr;
        //if it has to set the dir and the path
    } else {
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

        Var *a = new Var(0, dir, path);
        if (simMap->count(path)) {
            if (varsMap->count(name)) {
                (*varsMap)[name]->setDir(dir);
                if (path != (*varsMap)[name]->getPath()) {
                    simMap->insert({path, (*varsMap)[name]});
                }

            } else {
                (*simMap)[path]->setDir(dir);
                varsMap->insert({name, (*simMap)[path]});

            }
        } else {
            if (varsMap->count(name)) {
                (*varsMap)[name]->setDir(dir);
                simMap->insert({path, (*varsMap)[name]});
            } else {
                varsMap->insert({name, a});
                simMap->insert({path, a});
            }
        }
        delete a;
        a = nullptr;

    }

    return 2;

}
