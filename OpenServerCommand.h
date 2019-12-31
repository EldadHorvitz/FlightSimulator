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
#include "thread"
#include <arpa/inet.h>
#include <array>
#include <unordered_map>
#include <stdlib.h>
#include <chrono>
#include <mutex>

__attribute__((unused)) static bool isConnect = false;
__attribute__((unused)) static int client_socket_server;
__attribute__((unused)) static std::mutex m1;
__attribute__((unused)) static std::mutex m2;
__attribute__((unused)) static thread *threadGlobal = nullptr;


class OpenServerCommand : public Command {


public:
    OpenServerCommand();

    int execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) override;

    static int serverStart(double portNum, map<string, Var *> *varsMap, map<string, Var *> *simMap);

    static void readFromClient(map<string, Var *> *varsMap, map<string, Var *> *simMap);

    static void readFromBuffer(string buffer, map<string, Var *> *varsMap, map<string, Var *> *simMap);

    static void readFromBuffer1(string buffer, map<string, Var *> *varsMap, map<string, Var *> *simMap);

};


#endif //EX3_OPENSERVERCOMMAND_H
