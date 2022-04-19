#pragma once
#include <memory>
#include <unordered_map>
#include "ThreadPool.h"
#include "Socket.h"
#include "Epoll.h"
#include "ConnecterQueue.h"
#include "Connecter.h"

class Server{

#define BUFF_LEN 1000

private:
    std::unique_ptr<ThreadPool> threadpool;
    std::unique_ptr<Socket> sock;
    std::unique_ptr<Epoll> epoll;
    std::unordered_map<int, std::shared_ptr<Connecter_a>> clients;
    std::unique_ptr<ConnecterQueue_a> chattingroom;


    int server_fd;
    int epoll_fd;
    char BUFFER[BUFF_LEN];
public:
    Server();
    ~Server();
    void read_handler(int client_fd);
    void write_handler(int client_fd);
    void connect_handler(int client_fd);
    void work_handler();
    void start();
    void close_client(int client_fd);
};