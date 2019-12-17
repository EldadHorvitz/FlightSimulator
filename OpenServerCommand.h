//
// Created by eldad on 18/12/2019.
//

#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H


#include "Command.h"

class OpenServerCommand : public Command {

public:
    OpenServerCommand();
    int execute(vector<string> v, int index) override;
};


#endif //EX3_OPENSERVERCOMMAND_H
