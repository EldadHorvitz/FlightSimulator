//
// Created by nizan on 18/12/2019.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H


#include "Command.h"
#include "AssignmentCommand.h"

class DefineVarCommand : public Command {
public:

    DefineVarCommand();

    int execute(vector<string> v, int index,map<string, Var *> *varsMap,map<string, Var *> *simMap) override;

};


#endif //EX3_DEFINEVARCOMMAND_H
