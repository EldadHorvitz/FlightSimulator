//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include "SleepCommand.h"

SleepCommand::SleepCommand() { this->parmeterNum = 1; }

int SleepCommand::execute(vector<string> v, int index) {
    cout << parmeterNum << endl;
    return this->parmeterNum;
}
