#pragma once
#include <functional>
#include <memory>
#include "Channel.h"
#include "Epoll.h"
#include <thread>
#include <assert.h>
#include <mutex>
#include <condition_variable>
#include <sys/socket.h>

// 具体的操作在channel进行，这里只是提供接口
class EventLoop
{
public:
    using Functor = std::function<void()>;
    EventLoop();
    ~EventLoop();
    // 核心函数 loop相关处理
    void loop();
    void quit();

    void runInLoop(const Functor &cb); // 在当前线程就直接运行
    void queueInLoop(const Functor &cb); // 不在当前线程就排队运行
    
    bool isInLoopThread() {
        return threadId_ == std::this_thread::get_id();
    }
    void assertInLoopThread() { assert(isInLoopThread()); }

    // 操作 epoll 调用poll的接口进行操作
    void epollAdd(std::shared_ptr<Channel> channel, int timeout = 0) {
        epoller_->epollAdd(channel, timeout);
    }
    void epollMod(std::shared_ptr<Channel> channel, int timeout = 0) {
        epoller_->epollMod(channel, timeout);
    }
    void epollDel(std::shared_ptr<Channel> channel) {
        epoller_->epollDel(channel);
    }

    void shutdown(std::shared_ptr<Channel> channel);

    void WakeUp();
    void handleRead();
    void handleConnect();
    void doPendingFunctors();
    
private:
    std::shared_ptr<Epoll> epoller_;
    std::thread::id  threadId_; // 在构造的时候进行初始化，调用get_id()
    bool quit_ {false};
    bool looping_ {false};
    int wakeupFd_;
    std::shared_ptr<Channel> wakeupChannel_; // eventfd对应的channel

    std::mutex mutex_;
    std::vector<Functor> pendingFuntors_;
    bool callingPendingFunctors_ {false};
};