//
// Created by nizan on 18/12/2019.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H


#include "Command.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

class ConnectCommand : public Command {
public:
    ConnectCommand();

    int execute(vector<string> v, int index) override;

   static  int clientStart(int port, const char *ip);
};


#endif //EX3_CONNECTCOMMAND_H
