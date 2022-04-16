// #include "Epoll.h"
#include "../include/Epoll.h"

Epoll::Epoll(int epoll_size_, int server_fd_){
    epoll_size = epoll_size_;
    server_fd = server_fd_;

    event_list = new epoll_event[epoll_size];

    bzero(event_list, epoll_size * sizeof(*event_list));
    bzero(&event, sizeof(event));

    epoll_fd = epoll_create1(0); // 创建 epoll fd
    errif(epoll_fd < 0, "epoll create error");

    addFd(server_fd_, EPOLLIN); // 将 server fd注册
}

Epoll::~Epoll()
{
    delete[] event_list;
}

void Epoll::addFd(int fd, uint32_t mode){
    bzero(&event, sizeof(event));
    event.data.fd = fd;
    event.events = mode;

    int ctl_ = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event); // fd 注册到 epoll 红黑树上
    errif(ctl_ < 0, "epoll add error");
}
void Epoll::delFd(int fd){
    int del_ = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
    errif(del_ < 0, "epoll delete error");

}
int Epoll::wait(){
    int n = epoll_wait(epoll_fd, event_list, epoll_size, -1);
    return n;
}
int Epoll::getClientFd(int idx){
    /*  
        返回就绪队列中第idx个有事件发生的fd
    */
    return event_list[idx].data.fd;
}