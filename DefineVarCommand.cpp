//
// Created by nizan on 18/12/2019.
//

#include "DefineVarCommand.h"

DefineVarCommand::DefineVarCommand() { this->parmeterNum = 4; }

int DefineVarCommand::execute(vector<string> v, int index) {
    return this->parmeterNum + 1;
}
