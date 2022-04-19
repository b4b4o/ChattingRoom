#pragma once
class Connecter_a;
class ConnecterQueue_a
{
private:
    /* data */
public:

    virtual void notify(int server_fd, int mask_fd, char* buf, int len) = 0;
    virtual void join(Connecter_a* client) = 0;
    virtual void detach(Connecter_a* client) = 0;
    virtual void detachall() = 0;
    virtual int  size() = 0;
};
