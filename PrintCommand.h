//
// Created by nizan on 19/12/2019.
//

#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H


#include "Command.h"

class PrintCommand : public Command {
public:
    PrintCommand();

    int execute(vector<string> v, int index) override;

};


#endif //EX3_PRINTCOMMAND_H
