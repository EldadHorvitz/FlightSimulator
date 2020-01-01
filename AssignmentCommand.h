//
// Created by nizan on 19/12/2019.
//

#ifndef EX3_ASSIGNMENTCOMMAND_H
#define EX3_ASSIGNMENTCOMMAND_H


#include "Command.h"
#include "ConnectCommand.h"

__attribute__((unused)) static Var *globalVarAssignment = nullptr;

class AssignmentCommand : public Command {
public:
    AssignmentCommand();

    int execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) override;

    virtual ~AssignmentCommand();


};


#endif //EX3_ASSIGNMENTCOMMAND_H
