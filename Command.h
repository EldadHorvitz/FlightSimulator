//
// Created by eldad on 17/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <string>
#include <vector>
#include "map"
#include "Var.h"

using namespace std;

class Command {
public:

    virtual int execute(vector<string> v, int index,map<string, Var *> *varsMap,map<string, Var *> *simMap) = 0;

    virtual ~Command() {}

protected:
    map<string, Command *> varsMapC;
};


#endif //EX3_COMMAND_H
