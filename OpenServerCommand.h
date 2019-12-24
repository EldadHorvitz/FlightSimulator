//
// Created by eldad on 18/12/2019.
//

#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H


#include "Command.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>

#include <arpa/inet.h>
#include <array>
#include <unordered_map>
#include <stdlib.h>
#include <chrono>

class OpenServerCommand : public Command {


public:
    OpenServerCommand();

    int execute(vector<string> v, int index,map<string, Var *> *varsMap,map<string, Var *> *simMap) override;

    static int serverStart(double portNum);
};


#endif //EX3_OPENSERVERCOMMAND_H
