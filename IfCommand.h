//
// Created by nizan on 19/12/2019.
//

#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H


#include "Command.h"

class IfCommand : public Command  {
public:
    IfCommand();

    int execute(vector<string> v, int index,map<string, Var *> *varsMap,map<string, Var *> *simMap) override;
    map<string, Command *> initilize();
    string RemoveChar(string str, char c);
    void miniParser(int x , int num,vector<string> v,map<string, Var *> *varsMap,map<string, Var *> *simMap);
};


#endif //EX3_IFCOMMAND_H
