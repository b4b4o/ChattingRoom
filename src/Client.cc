#include "../include/Client.h"

Client::Client(){
    std::unique_lock<std::mutex> lock(mtx);
    is_exit = false;
}
Client::~Client()
{
    close(client_fd);
    std::cout << "客户端已结束" << '\n';
}
void Client::start(){
    sock = std::unique_ptr<Socket>(
        new Socket(
            false               // isServer
        )
    );
    
    client_fd = sock->getFd();
    setNonBlock();

    rd_t = std::unique_ptr<std::thread>(
        new std::thread(
            &Client::read_handler, this
        )
    );

    wr_t = std::unique_ptr<std::thread>(
        new std::thread(
            &Client::write_handler, this
        )
    );
    rd_t->join();
    wr_t->join();
}
void Client::read_handler(){
    int &fd = client_fd;
    while(1){

         // 每次判断是否写端要求退出，若是，则读端也跟着退出
        std::unique_lock<std::mutex> lock(mtx);
        if(is_exit)break;
        mtx.unlock();

        int tot_readlen = 0;
        while(1){

            int readlen = read(fd, RD_BUFFER + tot_readlen, BUFF_LEN - 1 - tot_readlen);
            // if(readlen != -1)
            // std::cout << "readlen : " << readlen << '\n';

            if(readlen < 0){
                if(errno == EAGAIN)break; // read over
                else{
                    std:: cout << "??" << '\n';
                }
            }else if(readlen == 0){
                //server close
                std :: cout << "服务器端断开连接"<< '\n';
                mtx.lock();
                is_exit = true;
                mtx.unlock();
                break;
            }else{
                tot_readlen += readlen;
            }
        }
        mtx.lock();

        if(is_exit)break;
        RD_BUFFER[tot_readlen] = '\0';
        // cout << "\t从服务器读到信息, " << "长度为 : "<< readlen << ", 内容为 : ";
        if(tot_readlen)
            std::cout << RD_BUFFER << '\n';

        mtx.unlock();
    }
    std:: cout << "读端已关闭" << '\n';
}
void Client::write_handler(){
    int &fd = client_fd;
    while(1){
        {
            std::unique_lock<std::mutex> lock(mtx);
            if(is_exit)break;
        }
        // cout << "I:\n";
        // cin.getline(BUFFER, BUFF_LEN);
        sleep(1.0 * (rand() % 100 + 1000) / 1000);
        std::string rd;
        for(int i = 0; i < rand() % 5 + 1; i++){
            rd += (char)('a' + rand() % 26);
        }
        strcpy(WR_BUFFER, rd.c_str());
        WR_BUFFER[rd.size()] = '\0';
        if(strcmp(WR_BUFFER, "q") == 0){
            std::cout << "出现q了" << '\n';
            std::unique_lock<std::mutex>lock(mtx);
            is_exit = true;
            break;
        }
        int wt = write(fd, WR_BUFFER, strlen(WR_BUFFER));
        std :: cout << "[客户端发送内容:] " << WR_BUFFER << '\n';
    }
    std::cout << "写端已退出" << '\n';
}
void Client::setNonBlock(){
    int oldflags = fcntl(client_fd, F_GETFL, 0);
    fcntl(client_fd, F_SETFL, oldflags | O_NONBLOCK);
}