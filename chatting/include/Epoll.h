#pragma once
#include <sys/epoll.h>
#include <malloc.h>
#include <string.h>
#include "error.h"

class Epoll
{
private:
    int epoll_fd;
    int server_fd;
    int epoll_size;
    epoll_event event;
    epoll_event *event_list;
public:

    Epoll(int epoll_size_, int server_fd_);
    ~Epoll();
    int wait();
    void addFd(int fd, uint32_t mode = (EPOLLIN | EPOLLET));
    void delFd(int fd);
    int getEpollFd(){return epoll_fd;}
    int getClientFd(int idx);
};

