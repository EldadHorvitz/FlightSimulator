//
// Created by nizan on 18/12/2019.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H


#include "Command.h"

class DefineVarCommand : public Command {
public:
    double val;
    string name;
    DefineVarCommand();

    int execute(vector<string> v, int index) override;

};


#endif //EX3_DEFINEVARCOMMAND_H
