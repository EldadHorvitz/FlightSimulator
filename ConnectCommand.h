//
// Created by nizan on 18/12/2019.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H


#include "Command.h"

class ConnectCommand : public Command {
public:
    ConnectCommand();
    int execute(vector<string> v, int index) override;

};


#endif //EX3_CONNECTCOMMAND_H
