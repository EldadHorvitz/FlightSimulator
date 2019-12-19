//
// Created by nizan on 18/12/2019.
//

#include <iostream>
#include "OpenServerCommand.h"

OpenServerCommand::OpenServerCommand() {
    this->parmeterNum = 1;
}

int OpenServerCommand::execute(vector<string> v, int index) {
    cout<<parmeterNum<<endl;

    return this->parmeterNum + 1;
}
