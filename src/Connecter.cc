#include "Connecter.h"

int Connecter::totids = 0;

void Connecter::reset(){
    username = "";
    userid = -1;
    cfd = -1;
}
void Connecter::setname(std::string username_){username = username_;}
bool inline Connecter::isvalid(){return cfd != -1;}
std::string& Connecter::name(){return username;}
int& Connecter::id(){return userid;}
int& Connecter::fd(){return cfd;}
void inline Connecter::update(const char* str, int len){
    write(cfd, str, len);
}
void Connecter::join(ConnecterQueue_a* chattingroom){
    // 单方面join
    subscribe_list.insert(chattingroom);
}
void Connecter::detach(ConnecterQueue_a* chattingroom){
    // 单方面detach
    auto chat = subscribe_list.find(chattingroom);
    if(chat != subscribe_list.end()){
        subscribe_list.erase(chat);
    }
}
void Connecter::detachall() {
    for(auto chattingroom: subscribe_list){
        chattingroom->detach(this);
    }
}