//
// Created by nizan on 18/12/2019.
//

#include <iostream>
#include <cstring>
#include "ConnectCommand.h"

ConnectCommand::ConnectCommand() {
    this->parmeterNum = 2;
}

int ConnectCommand::execute(vector<string> v, int index) {
    cout<<parmeterNum<<endl;
    int portNum=stoi(v[index+2]);
    char const *ip=v[index+2].c_str();
    int result= clientConnect(portNum,ip);
    if (result==0) {
        return this->parmeterNum + 1;
    } else{
        throw "error";
    }
    return parmeterNum + 1;
}


int ConnectCommand::clientConnect(int port, char const *ip)
{
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ip);  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }

    //if here we made a connection
    char hello[] = "Hi from client";
    int is_sent = send(client_socket , hello , strlen(hello) , 0 );
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"Hello message sent to server" <<std::endl;
    }

    char buffer[1024] = {0};
    int valread = read( client_socket , buffer, 1024);
    std::cout<<buffer<<std::endl;

    close(client_socket);

    return 0;
}
