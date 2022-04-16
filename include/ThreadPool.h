#pragma once

#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<functional>

class ThreadPool
{
private:
    /* data */
    struct Pool{
        std::queue<std::function<void()>>   tasks_q;
        std::mutex                          mtx;
        std::condition_variable             cv;
        bool                                isClosed;
    };
    std::shared_ptr<Pool>pool_;

public:
    explicit ThreadPool(int threadNum = 8);

    ThreadPool() = default;
    ThreadPool(ThreadPool &&) = default;

    ~ThreadPool();
    
    template<typename F>
    void addtask(F && f){
        std::unique_lock<std::mutex>lock(pool_ -> mtx);
        pool_ -> tasks_q.emplace(std::forward<F>(f));
        pool_ -> cv.notify_one();
    }
};
