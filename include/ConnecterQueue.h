
#pragma once
#include <string>
#include <set>
#include <unistd.h>
#include "Connecter_a.h"
#include "ConnecterQueue_a.h"
#define Q_LEN 5

class ConnecterQueue: public ConnecterQueue_a{

    public:
        ConnecterQueue(int max_size_);
        void reset();
        virtual int size() override;
        bool full();
        bool push( Connecter_a* c);
        void pop( Connecter_a* c);
        virtual void notify(int server_fd, int mask_fd, char* buf, int len) override;
        virtual void join( Connecter_a* client) override;
        virtual void detach( Connecter_a* client) override;
        virtual void detachall() override;
    private:
        std::set<Connecter_a *> c_queue;
        int max_size;
};