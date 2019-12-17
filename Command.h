//
// Created by eldad on 17/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <string>
#include <vector>

using namespace std;

class Command {
public:
    int parmeterNum;
    virtual int execute(vector<string> v,int index) = 0;
    virtual ~Command() {}
};


#endif //EX3_COMMAND_H
