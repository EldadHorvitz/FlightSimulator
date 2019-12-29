//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include "AssignmentCommand.h"
#include "Interpreter.h"

AssignmentCommand::AssignmentCommand() {}

int AssignmentCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    string var = v[index + 1];
    var = var.substr(1, var.length());
    Interpreter *i1 = new Interpreter();
    Expression *ex = i1->interpret(var, varsMap);
    Var * s=(*varsMap)[v[index]];
    s->setVal(ex->calculate());
    if (s->getDir()==1){
    //send s to the simulator through the static func

    }

    return 2;
}
