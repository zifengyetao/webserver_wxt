#include "EventLoopThreadPool.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, int threadNum):
    baseLoop_(baseLoop),
    threadNum_(threadNum),
    epoller_(new Epoll())
{

}

void EventLoopThreadPool::start()
{
    baseLoop_->assertInLoopThread();

    for (int i = 0; i < threadNum_; ++i) {
        std::shared_ptr<EventLoopThread> t(new EventLoopThread());
        threads_.push_back(t);
        workLoops_.push_back(t->startLoop()); // 线程池创建了指定数的线程，同时每个线程对应同样数目的loop
    }
    started_ = true;
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
    baseLoop_->assertInLoopThread();
    assert(started_);
    EventLoop *loop = baseLoop_; // 为什么用baseLoop_做初始化
    // 轮询机制
    if (!workLoops_.empty()) {
        loop = workLoops_[nextLoop_];
        nextLoop_ = (nextLoop_ + 1) % threadNum_;
    }
    return loop;
}

EventLoopThreadPool::~EventLoopThreadPool()
{
}
