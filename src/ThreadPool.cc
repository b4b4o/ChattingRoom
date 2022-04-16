// #include "ThreadPool.h"
#include "../include/ThreadPool.h"

ThreadPool::ThreadPool(int threadNum){
    pool_ = std::make_shared<Pool>();
    for(int i = 0; i < threadNum; i++){
        std::thread([this](){
            std::unique_lock<std::mutex>lock(pool_ -> mtx);
            while(true){
                if(!pool_ -> tasks_q.empty()){
                    auto task = std::move(pool_ -> tasks_q.front());
                    pool_ -> tasks_q.pop();
                    lock.unlock();

                    task();

                    lock.lock();
                }else if(pool_ -> isClosed)break;
                else{
                    pool_ -> cv.wait(lock);
                }
            }
        }).detach();
    }
}

ThreadPool::~ThreadPool(){
    if(pool_){
        {
            std::unique_lock<std::mutex>lock(pool_ -> mtx);
            pool_ -> isClosed = true;
        }
        
        pool_ -> cv.notify_all();
    }
}