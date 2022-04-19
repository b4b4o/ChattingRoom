#include "ConnecterQueue.h"
#include <iostream>
ConnecterQueue::ConnecterQueue(int max_size_){
    max_size = max_size_;
    reset();
}
void ConnecterQueue::reset(){
    c_queue.clear();
}
int ConnecterQueue::size(){
    return static_cast<int>(c_queue.size());
}
bool ConnecterQueue::full(){
    return size() >= max_size;
}
bool ConnecterQueue::push( Connecter_a* c){
    if(!full()){
        c_queue.insert(c);
        return true;
    }else return false;
}
void ConnecterQueue::pop( Connecter_a* c){
    auto find_ = c_queue.find(c);
    if(find_ != c_queue.end()){
        c_queue.erase(find_);
    }
}

void ConnecterQueue::notify(int server_fd, int mask_fd, char* buf, int len){

    for(auto it:c_queue){
        it->update(buf, len);
    }
}
void ConnecterQueue::join( Connecter_a* client){
    client->join(this);
    
    push(client);
}
void ConnecterQueue::detach( Connecter_a* client){
    client->detach(this);
    pop(client);
}
void ConnecterQueue::detachall(){
    for(auto client:c_queue){
        detach(client);
    }
}