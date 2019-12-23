//
// Created by nizan on 18/12/2019.
//

#include <iostream>
#include "DefineVarCommand.h"
#include "Var.h"

DefineVarCommand::DefineVarCommand() { this->parmeterNum = 4; }

int DefineVarCommand::execute(vector<string> v, int index) {
    int i=0;
    char c=v[index+1][i];
    string name;
    double val;
    int dir;
    string path;
   while(c!='\n'){

       i++;
       c=v[index+1][i];
   }
    return 2;
}
