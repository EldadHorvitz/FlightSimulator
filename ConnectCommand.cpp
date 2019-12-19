//
// Created by nizan on 18/12/2019.
//

#include <iostream>
#include "ConnectCommand.h"

ConnectCommand::ConnectCommand() {
    this->parmeterNum = 2;
}

int ConnectCommand::execute(vector<string> v, int index) {
    cout<<parmeterNum<<endl;

    return parmeterNum + 1;
}
