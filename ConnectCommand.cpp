//
// Created by nizan on 18/12/2019.
//

#include "ConnectCommand.h"

ConnectCommand::ConnectCommand() {
    this->parmeterNum = 2;
}

int ConnectCommand::execute(vector<string> v, int index) {
    return parmeterNum + 1;
}
