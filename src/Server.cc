#include <errno.h>
#include <fcntl.h>
// #include "Server.h"
#include "../include/Server.h"

Server::Server(){
    
    threadpool = std::unique_ptr<ThreadPool>(new ThreadPool(8));
    sock = std::unique_ptr<Socket>(
        new Socket(
            true    // isServer
        )
    );
    server_fd = sock->getFd();

    std::cout << "服务器已启动，等待连接." << '\n';
    cq.reset();

    epoll = std::unique_ptr<Epoll>(
        new Epoll(
            128               // epoll size
            , server_fd         // server_fd
        )
    );
    
    epoll_fd = epoll->getEpollFd();
    
}
Server::~Server(){
    close(server_fd);
    close(epoll_fd);
    cq.closeall();
    std::cout << "服务器已关闭" << '\n';
}
void Server::read_handler(int cfd){

    std::string head = "客户" + std::to_string(cfd) + ": ";

    BUFFER[0] = '\0';

    int rd_len = 0;
    while(1){
        rd_len = read(cfd, BUFFER, BUFF_LEN - 1);
        std::cout << "rdlen : " << rd_len << '\n';
        if(rd_len == 0){
            // 客户端断开连接
            epoll->delFd(cfd);

            Connecter conn(cfd);
            cq.pop(conn);
            close(cfd);
            std::cout << "关闭客户端 " << cfd << '\n';
            break;
        }else if(rd_len < 0){
            if(errno == EAGAIN || errno == EWOULDBLOCK){
                // 读取完毕
                cq.sendall(server_fd, cfd, (char *)(head.c_str()), strlen(head.c_str()));
                std::cout << "[送出消息:]" << head.c_str() << '\n';
                break;
            }else{
                epoll->delFd(cfd);

                Connecter conn(cfd);
                cq.pop(conn);
                close(cfd);
                std::cout << "关闭客户端 " << cfd << '\n';
                break;
            }
        }else{
            BUFFER[rd_len] = '\0';
            head += BUFFER;
            std::cout << "[收到客户端 " << cfd << " 消息:]" << BUFFER << '\n';
        }
    }
}
void Server::connect_handler(int client_fd){
    if(cq.full()){
        std::cout << "已满，连接失败"<< '\n';
        close(client_fd);
    }else{    
        // non block
        int oldflag = fcntl(client_fd, F_GETFL, 0);
        fcntl(client_fd, F_SETFL, oldflag | O_NONBLOCK);

        epoll->addFd(client_fd);

        Connecter conn(client_fd);
        cq.push(conn);
        std::cout << "客户连接成功" << '\n';
    }
}
void Server::work_handler(){

    while(1){

        int epoll_n = epoll -> wait();
        
        if(epoll_n == -1)break;

        for(int i = 0; i < epoll_n; i++){
                
            if(epoll->getClientFd(i) == server_fd){
                int client_fd = sock -> accept_();
                if(client_fd == -1){
                    continue;
                }else{
                    connect_handler(client_fd);
                }
            }else{
                // 读写
                int fd = epoll->getClientFd(i);
                threadpool->addtask(std::bind(&Server::read_handler, this, fd));
            }
        }
    }
}
void Server::start(){
    std::thread t_main_worker(
        &Server::work_handler, this
    );
    t_main_worker.join();
}