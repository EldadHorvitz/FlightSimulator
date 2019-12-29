//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include "AssignmentCommand.h"
#include "Interpreter.h"

AssignmentCommand::AssignmentCommand() {}

int AssignmentCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    string var = v[index + 1];
    var = var.substr(1, var.length());
    Interpreter *i1 = new Interpreter();
    Expression *ex = i1->interpret(var, varsMap);
    if (!varsMap->count(v[index])){
        varsMap->insert({v[index], new Var(-999,-1,"")});
    }
    Var * s=(*varsMap)[v[index]];
    s->setVal(ex->calculate());
    if (s->getDir()==1){
        string message="set "+s->getPath()+" "+to_string(s->getVal())+ "\r\n";
        ssize_t returl_val = write(client_socket_client, message.c_str(), message.length());
        /*
        char p[message.length()];
        for (int i = 0; i < sizeof(p); i++) {
            p[i] = message[i];
        }
        int is_sent = send(client_socket_client, p, strlen(p), 0);
        if (is_sent == -1) {
            std::cout << "Error sending message" << std::endl;
        } else {
            std::cout << "Hello message sent to Server" << std::endl;
        }
*/


    }

    return 2;
}
