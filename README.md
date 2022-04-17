# 基于Socket的聊天室
## 更新日志
| version   | date      | message   |
| ----      |    ----   | ----      |
|v1.2       |   4-17    |对Client端*输入q无法主动关闭*的bug进行了修复|
|v1.1       |   4-17    |进行Client端代码重构|
|v1.0       |   4-16    |进行Server端代码重构|
## Todo List

|feature|bug| description|
|----|----|----|
| &#x2714; ||观察者模式 所有订阅者最后都将被close,并且向所有订阅者发送消息|
| |&#x2714; |读端最后一个client退出会 read阻塞|
| &#x2714; ||定时器关闭|
| &#x2714; ||测试代码|
| &#x2714; ||lazy pool|
| &#x2714; ||prebuffer|

## 特点
基于Socket网络编程

支持Epoll多路复用，采用主从Reactor模式

采用线程池

采用RAII智能指针防止内存泄漏
## 目录介绍
/bin :      Cmake && make 生成二进制文件

/include :  headers

/log:       Todo & Done List

/src:       source codes
## 编译方法
mkdir build

cd build

cmake ..

make

## 在编写的时候遇到的一些问题
1.重构时 Template 写在 CC 文件中导致 undefined reference to 'My Function'

2.对于类的非静态函数，需要以这样的方式传入：
std::thread t_main_worker(
        &Server::work_handler, this
);

而不是：
std::thread t_main_worker(
        work_handler
);

3.编译时需要根据头文件的引用顺序来，否则会导致有些 undefined reference