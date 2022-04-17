#pragma once
#include <memory>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <fcntl.h>
#include "Socket.h"

class Client{
    #define BUFF_LEN 1000
private:
    std::unique_ptr<Socket>sock;
    int client_fd;
    std::unique_ptr<std::thread> rd_t, wr_t;
    char WR_BUFFER[BUFF_LEN];
    char RD_BUFFER[BUFF_LEN];

    bool is_exit;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Client();
    ~Client();
    void read_handler();
    void write_handler();
    void setNonBlock();
    void start();
};

