// #include "Socket.h"
#include "../include/Socket.h"
Socket::Socket(bool isServer_, const char* ip_, int port_){
    isServer = isServer_;


    bzero(&sock_addr, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port_);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    fd = socket(PF_INET, SOCK_STREAM, 0);
    errif(fd < 0, "socket create error");    

    if(isServer){
        // Server    
        bind_();
        listen_();
    }else{
        // Client
        // sock_addr.sin_addr.s_addr = htonl(atoi(ip_));
        sock_addr.sin_addr.s_addr = inet_addr(ip_);
        connect_();
    }
}

Socket::~Socket(){
    if(fd != -1){
        std::cout << "关闭fd: " << fd << '\n';
        close(fd);
        fd = -1;
    }
}

void Socket::connect_(){
    errif(connect(fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)), "connect error");
    printf("connect finished\n");
}
int Socket::accept_(){
    socklen_t len = sizeof(sock_addr);
    int client_fd = accept(fd, (struct sockaddr *)&sock_addr, &len);
    errif(client_fd < 0, "accept error");
    return client_fd;
}
void Socket::bind_(){
    errif(bind(fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)), "bind error");
}
void Socket::listen_(){
    errif(listen(fd, SOMAXCONN) < 0, "listen error");
}
int Socket::getFd(){
    return fd;
}