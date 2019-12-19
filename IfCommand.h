//
// Created by nizan on 19/12/2019.
//

#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H


#include "Command.h"

class IfCommand : public Command  {
public:
    IfCommand();

    int execute(vector<string> v, int index) override;

};


#endif //EX3_IFCOMMAND_H
