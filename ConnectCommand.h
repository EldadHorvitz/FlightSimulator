//
// Created by nizan on 18/12/2019.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Command.h"

class ConnectCommand : public Command {
public:
    ConnectCommand();
    int execute(vector<string> v, int index) override;

    int clientConnect(int port, char const *ip);

};


#endif //EX3_CONNECTCOMMAND_H
