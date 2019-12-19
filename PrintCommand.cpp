//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include "PrintCommand.h"

PrintCommand::PrintCommand() {
    this->parmeterNum = 1;
}

int PrintCommand::execute(vector<string> v, int index) {
    cout << parmeterNum << endl;
    return this->parmeterNum;
}
