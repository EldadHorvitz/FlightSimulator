//
// Created by nizan on 19/12/2019.
//

#ifndef EX3_ASSIGNMENTCOMMAND_H
#define EX3_ASSIGNMENTCOMMAND_H


#include "Command.h"

class AssignmentCommand : public Command{
public:
    AssignmentCommand();

    int execute(vector<string> v, int index) override;

};


#endif //EX3_ASSIGNMENTCOMMAND_H
