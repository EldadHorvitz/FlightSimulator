//
// Created by nizan on 18/12/2019.
//


#include <thread>
#include "OpenServerCommand.h"
#include <cstring>
#include <mutex>
#include <arpa/inet.h>
#include "Interpreter.h"
#include <string>
#include <iostream>

OpenServerCommand::OpenServerCommand() {

}

//excuting the Open Data Server Command
int OpenServerCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    Interpreter *i1 = new Interpreter();
    string port = v[index + 1];
    port = port.substr(0, port.length() - 1);
    Expression *ex = i1->interpret(port, varsMap);
    double portNum = ex->calculate();
    delete i1;
    i1 = nullptr;
    serverStart(portNum, varsMap, simMap);
    int result = 0;
    if (result == 0) {
        return 2;
    } else {
        throw "error";
    }

}

//starrting the server
int OpenServerCommand::serverStart(double portNum, map<string, Var *> *varsMap, map<string, Var *> *simMap) {

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr << "could not create a socket" << endl;
        return -1;
    }
    //bind socket to IP address
    //we first create the sockaddr obj.
    sockaddr_in address;//in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//give me any IP allocated for my machine.
    // address.sin_addr.s_addr = inet_addr("10.0.2.2");
    address.sin_port = htons(portNum);
    //we need to convert our number
    //to a number that the network understands

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "could not bind socket to an IP" << endl;
        return -1;
    }

    if (listen(socketfd, 1) == -1) {
        cerr << "Error during listening command" << endl;
    }
    // accepting a client
    int addrlen = sizeof(address);
    client_socket_server = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &addrlen);

    if (client_socket_server == -1) {
        cerr << "Error accepting" << endl;
        return -1;
    }
    close(socketfd);
    isConnect = true;
    thread *t1 = new thread(readFromClient, varsMap, simMap);
    threadGlobal = t1;
    return 1;
}

//reading from the client in a thread
void  OpenServerCommand::readFromClient(map<string, Var *> *varsMap, __attribute__((unused)) map<string, Var *> *simMap) {
    m2.lock();
    string s = "";
    while (isConnect) {
        //reading from client
        char buffer[1024] = {0};
        read(client_socket_server, buffer, 1024);
        string delimiter = "\n";
        s += buffer;
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            readFromBuffer(token, varsMap, simMap);
            s.erase(0, pos + delimiter.length());
        }
    }
    m2.unlock();
}

//reading from the given buffer and updating it in the symbol table
void OpenServerCommand::readFromBuffer(string buffer, map<string, Var *> *varsMap,
                                       __attribute__((unused)) map<string, Var *> *simMap) {
    m1.lock();
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token[36];
    int i = 0;
    while ((pos = buffer.find(delimiter)) != std::string::npos) {
        token[i] = buffer.substr(0, pos);
        buffer.erase(0, pos + delimiter.length());
        i++;
    }
    token[i] = buffer.substr(0, buffer.length());
    (*varsMap)["airspeed"]->setVal(stod(token[0]));
    (*varsMap)["warp"]->setVal(stod(token[1]));
    (*varsMap)["magnetos"]->setVal(stod(token[2]));
    (*varsMap)["heading"]->setVal(stod(token[3]));
    (*varsMap)["alt"]->setVal(stod(token[4]));
    (*varsMap)["altimeter"]->setVal(stod(token[5]));
    (*varsMap)["attitude"]->setVal(stod(token[6]));
    (*varsMap)["roll"]->setVal(stod(token[7]));
    (*varsMap)["pitch"]->setVal(stod(token[8]));
    (*varsMap)["attitude2"]->setVal(stod(token[9]));
    (*varsMap)["attitude3"]->setVal(stod(token[10]));
    (*varsMap)["pressure"]->setVal(stod(token[11]));
    (*varsMap)["gps"]->setVal(stod(token[12]));
    (*varsMap)["gps2"]->setVal(stod(token[13]));
    (*varsMap)["gps3"]->setVal(stod(token[14]));
    (*varsMap)["indicated"]->setVal(stod(token[15]));
    (*varsMap)["magnetic"]->setVal(stod(token[16]));
    (*varsMap)["slip"]->setVal(stod(token[17]));
    (*varsMap)["turn"]->setVal(stod(token[18]));
    (*varsMap)["vertical"]->setVal(stod(token[19]));
    (*varsMap)["aileron"]->setVal(stod(token[20]));
    (*varsMap)["elevator"]->setVal(stod(token[21]));
    (*varsMap)["rudder"]->setVal(stod(token[22]));
    (*varsMap)["flight_flaps"]->setVal(stod(token[23]));
    (*varsMap)["engine_throttle"]->setVal(stod(token[24]));
    (*varsMap)["throttle"]->setVal(stod(token[25]));
    (*varsMap)["masteravionics"]->setVal(stod(token[26]));
    (*varsMap)["starter"]->setVal(stod(token[27]));
    (*varsMap)["autostart"]->setVal(stod(token[28]));
    (*varsMap)["breaks"]->setVal(stod(token[29]));
    (*varsMap)["brakeparking"]->setVal(stod(token[30]));
    (*varsMap)["primer"]->setVal(stod(token[31]));
    (*varsMap)["mixture"]->setVal(stod(token[32]));
    (*varsMap)["masterbat"]->setVal(stod(token[33]));
    (*varsMap)["masterlat"]->setVal(stod(token[34]));
    (*varsMap)["rpm"]->setVal(stod(token[35]));
    m1.unlock();

}


