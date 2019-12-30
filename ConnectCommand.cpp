//
// Created by nizan on 18/12/2019.
//

#include <iostream>
#include <cstring>
#include <thread>
#include "ConnectCommand.h"
#include "Interpreter.h"

ConnectCommand::ConnectCommand() {

}

int ConnectCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    double port = 0;
    string portString = "";
    int flag = 0;
    for (char c:v[index + 1]) {
        if (c == ',') {
            flag = 1;
            continue;
        } else if (flag == 1 && c != ')') {
            portString += c;
        }
    }
    Interpreter *i1 = new Interpreter();
    Expression *ex = i1->interpret(portString, varsMap);
    port = ex->calculate();

    std::string str = v[index + 1].substr(1, 9);
    const char *cstr = str.c_str();
    clientStart(port, cstr, varsMap);
    delete i1;
    i1 = nullptr;
    return 2;
}


int ConnectCommand::clientStart(int port, const char *ip, map<string, Var *> *varsMap) {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of Server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ip);  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the Server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host Server" << std::endl;
        return -2;
    }
    Var *tr = new Var(client_socket, client_socket, "");
    varsMap->insert({"client_sock", tr});
    return 0;
}
