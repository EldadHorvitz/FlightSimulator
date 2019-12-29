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
    Var *s = (*varsMap)[v[index]];
    s->setVal(ex->calculate());
    if (s->getDir() == 1) {
        string massage = "";
        massage += s->getPath() + "" + to_string(s->getVal());
        char p[massage.length()];
        for (int i = 0; i < sizeof(p); i++) {
            p[i] = massage[i];
        }
        int is_sent = send(client_socket_client, p, strlen(p), 0);
        if (is_sent == -1) {
            std::cout << "Error sending message" << std::endl;
        } else {
            std::cout << "Hello message sent to Server" << std::endl;
        }


    }

    return 2;
}
