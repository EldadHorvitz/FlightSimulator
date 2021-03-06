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

__attribute__((unused)) static Var *tr = nullptr;
__attribute__((unused)) static int client_socket_client;

class ConnectCommand : public Command {
public:
    ConnectCommand();

    int execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) override;

    int clientStart(int port, const char *ip, map<string, Var *> *varsMap);
};


#endif //EX3_CONNECTCOMMAND_H
