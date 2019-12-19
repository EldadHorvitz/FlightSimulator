//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include "WhileCommand.h"

WhileCommand::WhileCommand() { this->parmeterNum = 2; }

int WhileCommand::execute(vector<string> v, int index) {
    cout << parmeterNum << endl;

    return this->parmeterNum;
}
