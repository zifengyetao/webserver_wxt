#include "EventLoopThread.h"
#include <functional>

EventLoopThread::EventLoopThread():
    loop_(nullptr),
    thread_(std::bind(&EventLoopThread::threadFunc, this), "EventLoopThread")
{

}

EventLoopThread::~EventLoopThread()
{
    // 销毁线程
    if (loop_ != NULL)
	{
		loop_->quit();
		thread_.join();
	}
}

EventLoop* EventLoopThread::startLoop()
{
    {
		// 主线程创建子线程成功后，阻塞在这里，等待子线程创建好Eventloop之后通过notify_all唤醒主线程
		std::unique_lock<std::mutex> lock(mutex_);
		while (loop_ == NULL)
		{
			condition_variable_.wait(lock);
		}
	}
    return loop_;
}

// 线程创建时的回调  主要是创建EventLoop，用loop_保存
void EventLoopThread::threadFunc()
{
    EventLoop loop;
    
    {
        std::unique_lock<std::mutex> lock(mutex_); // 获取锁
        loop_ = &loop;
        condition_variable_.notify_all();
    }

    loop.loop();

    loop_ = nullptr;
}