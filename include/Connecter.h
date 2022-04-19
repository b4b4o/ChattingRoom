#pragma once

#include <string>
#include <unistd.h>
#include <set>
#include "Connecter_a.h" 
#include "ConnecterQueue_a.h"

class Connecter : public Connecter_a{
private:
    std::string username;
    int userid;
    int cfd;//connect_fd
    std::set<ConnecterQueue_a *> subscribe_list;
    static int totids;
public:

    Connecter(int fd = -1) : username(""), userid(++totids), cfd(fd){
        printf("K1\n");
        subscribe_list.clear();
        printf("K2\n");
    }
    bool operator < (const Connecter &b)const {
        return cfd < b.cfd;
    }
    void reset();
    void setname(std::string username_);
    bool inline isvalid();
    std::string& name();
    int& id();
    virtual int& fd() override;
    virtual void update(const char* str, int len) override;
    virtual void join( ConnecterQueue_a * chattingroom) override;
    virtual void detach( ConnecterQueue_a* chattingroom) override;
    virtual void detachall() override;
};
