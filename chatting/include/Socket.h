#pragma once
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h> // bzero
#include <stdlib.h> // atoi
#include <unistd.h> // close
#include <iostream>
#include <arpa/inet.h> // inet_addr
#include "error.h"
class Socket
{
private:
    struct sockaddr_in sock_addr;
    int fd;
    bool isServer;
public:
    Socket(bool isServer_ = false, const char* ip_ = "101.43.205.213", int port_ = 6401);
    ~Socket();
    int getFd();
    int accept_();
    void bind_();
    void listen_();
    void connect_();
};

