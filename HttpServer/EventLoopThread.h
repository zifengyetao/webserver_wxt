#pragma once
#include "EventLoop.h"
#include <mutex>
#include <condition_variable>
#include <thread>

class EventLoopThread
{
public:
    EventLoopThread();
    ~EventLoopThread();

    EventLoop* startLoop();
private:
    void threadFunc(); // 创建线程时用于指定每个线程的回调函数
    EventLoop* loop_; // EventLoop
    std::thread thread_; // 线程
    // 多线程加锁，一般用互斥锁+条件变量
    std::mutex mutex_; // 互斥锁
    std::condition_variable condition_variable_; // 条件变量
};