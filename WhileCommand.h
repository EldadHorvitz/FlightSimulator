//
// Created by nizan on 19/12/2019.
//

#ifndef EX3_WHILECOMMAND_H
#define EX3_WHILECOMMAND_H


#include "Command.h"

class WhileCommand : public Command {
public:
    WhileCommand();

    int execute(vector<string> v, int index) override;

};


#endif //EX3_WHILECOMMAND_H
