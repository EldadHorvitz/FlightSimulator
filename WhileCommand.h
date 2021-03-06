//
// Created by nizan on 19/12/2019.
//

#ifndef EX3_WHILECOMMAND_H
#define EX3_WHILECOMMAND_H


#include "Command.h"

class WhileCommand : public Command {
public:
    WhileCommand();
    map<string, Command *> initilize();
    string RemoveChar(string str, char c);
    int execute(vector<string> v, int index,map<string, Var *> *varsMap,map<string, Var *> *simMap) override;
    void miniParser(int x , int num,vector<string> v,map<string, Var *> *varsMap,map<string, Var *> *simMap);

};


#endif //EX3_WHILECOMMAND_H
