//
// Created by eldad on 18/12/2019.
//

#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H

#include <iostream>
#include "thread"
#include <cstdlib>
#include "Command.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>


class OpenServerCommand : public Command {

public:
    OpenServerCommand();

    int execute(vector<string> v, int index) override;

    int serverStart(int PORT);

};


#endif //EX3_OPENSERVERCOMMAND_H
