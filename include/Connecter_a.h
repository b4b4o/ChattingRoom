#pragma once
class ConnecterQueue_a;
class Connecter_a
{
private:
    /* data */
public:

    virtual void update(const char* str, int len) = 0;
    virtual void join(ConnecterQueue_a* chattingroom) = 0;
    virtual void detach(ConnecterQueue_a* chattingroom) = 0;
    virtual void detachall() = 0;
    virtual int& fd() = 0;
    
};
