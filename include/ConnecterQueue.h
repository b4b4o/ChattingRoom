
#pragma once
#include <string>
#include <set>
#include <unistd.h>
#define Q_LEN 5
class Connecter{
private:
    std::string username;
    int userid;
    int cfd;//connect_fd
    int ids;
public:

    Connecter(int fd = -1):ids(0), username(""), userid(ids++), cfd(fd){}
    bool operator < (const Connecter &b)const {
        return cfd < b.cfd;
    }
    void reset(){
        username = "";
        userid = -1;
        cfd = -1;
    }
    void setname(std::string username_){username = username_;}
    bool isvalid(){return cfd != -1;}
    std::string& name(){return username;}
    int& id(){return userid;}
    int& fd(){return cfd;}
};
class ConnecterQueue{

    public:
        ConnecterQueue(){max_size = Q_LEN;}
        void reset(){
            c_queue.clear();
        }
        int size(){
            return c_queue.size();
        }
        bool full(){
            return size() >= max_size;
        }
        bool push(Connecter c){
            if(!full()){
                c_queue.insert(c);
                return true;
            }else return false;
        }
        void pop(Connecter c){
            auto find_ = c_queue.find(c);
            if(find_ != c_queue.end()){
                c_queue.erase(find_);
            }
        }
        void send(int fd, char *buf, int len){
            write(fd, buf, len);
        }
        void sendall(int server_fd, int mask_fd, char* buf, int len){
            for(auto it:c_queue){
                int &nowfd = it.fd();
                // if(nowfd == server_fd || nowfd == mask_fd)continue;
                if(nowfd == server_fd)continue;
                else{
                    send(nowfd, buf, len);
                }
            }
        }
        void closeall(){
            for(auto it:c_queue){
                int &nowfd = it.fd();
                close(nowfd);
            }
        }
    private:
        std::set<Connecter> c_queue;
        int max_size;
};