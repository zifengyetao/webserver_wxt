#pragma once
// 服务中心 监听socket对象，根据线程池分配线程，并启动任务
#include "EventLoop.h"
#include "Channel.h"
#include "EventLoopThreadPool.h"

#include <memory>

class Eventloop;
class Channel;
class EventLoopThreadPool;

class Server
{
public:
    Server(EventLoop* loop_, int threadNum, int port);
    ~Server();

    // 核心函数
    void start();

    // server可看作主线程，主要作用是监听事件，如果是监听事件，更新事件，如果是新连接的事件，创建socket，分配线程，挂上内核事件表
    void handleNewConnect();
    void handleThisConnect() { loop_->epollMod(acceptChannel_); }
private:
    EventLoop* loop_;
    std::shared_ptr<Channel> acceptChannel_; // accept 监听事件对应的channel
    // 线程池
    int threadNum_;
    std::unique_ptr<EventLoopThreadPool> threadPool_; // 线程池 分配线程
    int port_;
    // 监听fd
    int listenFd_;

    bool started_ {false};

    static constexpr int MAXFDS = 100000;
};