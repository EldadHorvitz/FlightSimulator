//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include "IfCommand.h"

IfCommand::IfCommand() { this->parmeterNum = 2; }

int IfCommand::execute(vector<string> v, int index) {
    cout << parmeterNum << endl;
    return this->parmeterNum;
}
