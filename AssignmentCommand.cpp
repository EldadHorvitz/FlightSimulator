//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include "AssignmentCommand.h"

AssignmentCommand::AssignmentCommand() { this->parmeterNum = 2; }

int AssignmentCommand::execute(vector<string> v, int index) {
    cout << parmeterNum << endl;

    return this->parmeterNum;
}
