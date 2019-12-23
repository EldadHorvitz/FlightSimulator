//
// Created by nizan on 18/12/2019.
//

#include <iostream>
#include <cstring>
#include <thread>
#include "ConnectCommand.h"

ConnectCommand::ConnectCommand() {

}

int ConnectCommand::execute(vector<string> v, int index) {
    int port = stoi(v[index + 2]);
    std::string str = v[index + 1];
    const char *cstr = str.c_str();
      thread *t1 = new thread(clientStart, port, cstr);
     t1->join();

    return 2;
}


int ConnectCommand::clientStart(int port, const char *ip) {

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
    } else {
        std::cout << "Client is now connected to Server" << std::endl;
    }

    //if here we made a connection
    char hello[] = "Hi from Client";
    int is_sent = send(client_socket, hello, strlen(hello), 0);
    if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
    } else {
        std::cout << "Hello message sent to Server" << std::endl;
    }

    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << buffer << std::endl;

    close(client_socket);

    return 0;
}
