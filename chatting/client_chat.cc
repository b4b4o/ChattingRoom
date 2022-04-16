#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<iostream>
#include<string.h>
#include<string>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<thread>

#include "Socket.h"

using namespace std;

#define BUFF_LEN 1000
char BUFFER[BUFF_LEN];
char RD_BUFFER[BUFF_LEN];

void read_handler(int fd){
    while(1){
        int readlen = read(fd, RD_BUFFER, BUFF_LEN - 1);
        // cout << "readlen : " << readlen << '\n';
        if(readlen <= 0)break;
        RD_BUFFER[readlen] = '\0';
        // cout << "\t从服务器读到信息, " << "长度为 : "<< readlen << ", 内容为 : ";
        cout << RD_BUFFER << '\n';
    }
}
void write_handler(int fd){
    while(1){
        // cout << "I:\n";
        // cin.getline(BUFFER, BUFF_LEN);
        sleep(1.0 * (rand() % 800 + 300) / 1000);
        string rd;
        for(int i = 0; i < rand() % 5 + 1; i++){
            rd += (char)('a' + rand() % 26);
        }
        strcpy(BUFFER, rd.c_str());
        BUFFER[rd.size()] = '\0';
        if(strcmp(BUFFER, "q") == 0)break;
        int wt = write(fd, BUFFER, strlen(BUFFER));
        // cout << wt << '\n';
    }
    cout << "已退出" << '\n';
    close(fd);
    exit(1);
}
int main(int argc, char* args[]){
    srand(time(NULL));

    unique_ptr<Socket> sock(
        new Socket(
            false               // isServer
            , "101.43.205.213"  // ip
            , 6401              // port
        )
    );

    cout << "成功连接" << '\n';
    int fd = sock->getFd();

    thread rd_t(read_handler, fd);
    thread wr_t(write_handler, fd);

    rd_t.join();
    wr_t.join();

    close(fd);
    return 0;
}