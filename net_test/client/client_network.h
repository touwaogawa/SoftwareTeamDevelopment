#ifndef CLIENT_NETWORK_H
#define CLIENT_NETWORK_H

#pragma once
#include <iostream>
#include <string>

class Network {
public:
    static bool Connect(int port, int clientID);
    static void ShutDown();
    
    template <typename T>
    static void SendData(const T& data);

    template <typename T>
    static T RecvData();
    
private:
    static int client_socket;
};

#endif
