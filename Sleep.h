//
// Created by nizan on 22/12/2019.
//

#ifndef EX3_SLEEP_H
#define EX3_SLEEP_H


#include "Command.h"

class Sleep : public Command {
public:
    int execute(vector<string> v, int index) override;


};


#endif //EX3_SLEEP_H
