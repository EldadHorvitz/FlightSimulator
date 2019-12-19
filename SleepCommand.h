//
// Created by nizan on 19/12/2019.
//

#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand : public Command {
public:
    SleepCommand();

    int execute(vector<string> v, int index) override;

};


#endif //EX3_SLEEPCOMMAND_H
