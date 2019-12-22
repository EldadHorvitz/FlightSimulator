//
// Created by nizan on 22/12/2019.
//

#ifndef EX3_PRINT_H
#define EX3_PRINT_H


#include "Command.h"

class Print : public Command {
public:
    int execute(vector<string> v, int index) override;

};


#endif //EX3_PRINT_H
