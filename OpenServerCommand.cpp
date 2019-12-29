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

int OpenServerCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    Interpreter *i1 = new Interpreter();
    string port = v[index + 1];
    port = port.substr(0, port.length() - 1);
    Expression *ex = i1->interpret(port, varsMap);
    double portNum = ex->calculate();
    serverStart(portNum, varsMap, simMap);
    int result = 0;
    if (result == 0) {
        return 2;
    } else {
        throw "error";
    }
}


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
    client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
    cout << "connected!!!!" << endl;
    if (client_socket == -1) {
        cerr << "Error accepting" << endl;
        return -1;
    }
    close(socketfd);

    isConnect = true;
    thread *t1 = new thread(readFromClient, varsMap, simMap);
    return 1;
}


void OpenServerCommand::readFromClient(map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    m2.lock();
    while (isConnect) {
        //reading from client
        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);
        //  int valread = read(client_socket, buffer, 1024);
        std::cout << buffer << std::endl;
        readFromBuffer(buffer, varsMap, simMap);
    }
    m2.unlock();
}

void OpenServerCommand::readFromBuffer(string buffer, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    m1.lock();
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token[36];
    int i = 0;
    while ((pos = buffer.find(delimiter)) != std::string::npos) {
        token[i] = buffer.substr(0, pos);
        cout << token << endl;
        buffer.erase(0, pos + delimiter.length());
        i++;
    }
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


    m1.unlock();

}

/*


//create socket
int socketfd = socket(AF_INET, SOCK_STREAM, 0);
if (socketfd == -1) {
    //error
    std::cerr << "Could not create a socket" << std::endl;
    return -1;
}

//bind socket to IP address
// we first need to create the sockaddr obj.
sockaddr_in address; //in means IP4
address.sin_family = AF_INET;
address.sin_addr.s_addr = inet_addr("127.0.0.1");
//   address.sin_addr.s_addr= INADDR_ANY; //give me any IP allocated for my machine
address.sin_port = htons(portNum);
//we need to convert our number
// to a number that the network understands.

//the actual bind command
if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    std::cerr << "Could not bind the socket to an IP" << std::endl;
    return -2;
}

//making socket listen to the port
if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
    std::cerr << "Error during listening command" << std::endl;
    return -3;
} else {
    std::cout << "Server is now listening ..." << std::endl;
}

// accepting a client
socklen_t addrlen = sizeof(sockaddr_in);
int client_socket = accept(socketfd, (struct sockaddr *) &address, &addrlen);
std::cout << "adfsadfdsfs" << std::endl;


if (client_socket == -1) {
    std::cerr << "Error accepting client" << std::endl;
    return -4;
}

close(socketfd); //closing the listening socket

//reading from client
char buffer[1024] = {0};
int valread = read(client_socket, buffer, 1024);
std::cout << buffer << std::endl;

//writing back to client
// char *hello = "";
//  send(client_socket , hello , strlen(hello) , 0 );
std::cout << "Hello message sent\n" << std::endl;
return 0;

}
*/