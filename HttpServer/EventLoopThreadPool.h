#pragma once
#include "EventLoop.h"
#include "Epoll.h"
#include "EventLoopThread.h"
#include <vector>

class EventLoopThreadPool
{
public:
    EventLoopThreadPool(EventLoop* loop, int threadNum);
    ~EventLoopThreadPool();
    void start();

    EventLoop* getNextLoop(); // 当来新的连接时，需要分配线程，分配线程实在后台的，实际是返回之前每个线程对应的EventLoop
private:
    EventLoop* baseLoop_; // 主线程
    int threadNum_ {0};
    std::shared_ptr<Epoll> epoller_;

    std::vector<std::shared_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> workLoops_; // 工作线程

    bool started_ {false};
    int nextLoop_;
};