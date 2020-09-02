#include "EventLoop.h"
#include <iostream>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>

using namespace std;

int createWakeUpFd()
{
    int fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (fd  < 0) {
        cout << "createWakeUpFd error " << endl;
        abort(); // 是否可以换成 exit()
    }
    return fd;
}

EventLoop::EventLoop():
    epoller_(new Epoll()),
    threadId_(std::this_thread::get_id()),
    quit_(false),
    looping_(false),
    wakeupFd_(createWakeUpFd()),
    wakeupChannel_(new Channel(this, wakeupFd_))
{
    wakeupChannel_->setEvents(EPOLLIN | EPOLLET); // 设置监听事件 可读事件 边沿触发
    wakeupChannel_->setReadCallBack(bind(&EventLoop::handleRead, this)); // 监听唤醒读事件回调  其实不用做啥 
    // wakeupChannel_->setWriteCallBack; // 写事件回调 不会监听写事件 因为不写
    wakeupChannel_->setConnectCallBack(bind(&EventLoop::handleConnect, this));

    epoller_->epollAdd(wakeupChannel_, 0);
}

EventLoop::~EventLoop() 
{
}

// 线程调用
void EventLoop::runInLoop(const Functor &cb)
{
    if (isInLoopThread()) {
        cb();
    } else {
        queueInLoop(cb);
    }
}
// 其他线程调用 需要排队处理，当前IO线程唤醒
void EventLoop::queueInLoop(const Functor &cb)
{
    // 代码块的作用是限制作用域
    {
        // 多个线程可能调用，需要加锁
        std::unique_lock<std::mutex> lock(mutex_);
        pendingFuntors_.push_back(cb);
    }

    if (!isInLoopThread() || callingPendingFunctors_) {
        WakeUp();
    }
}

void EventLoop::doPendingFunctors()
{
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        functors.swap(pendingFuntors_);
    }

    for (size_t i = 0; i < functors.size(); ++i) {
        functors[i]();
    }
    callingPendingFunctors_ = false;
}

void EventLoop::loop()
{
    assert(!looping_);
    assert(isInLoopThread()); // 是否可能不在当前线程？ 可能用户在其他线程调用了这个loop
    // looping_ = true; // 判断当前线程是否已经在loop，如果是 就不用重新启动循环，什么场景会有重复起循环呢，1. 调用错误，重复调用loop 2. 多进程，父进程fork子进程的时候，误调用两次loop 3. 多线程，其他线程调用了这个loop
    looping_ = true;
    quit_ = false;
    std::vector<std::shared_ptr<Channel>> activeChannel;
    while (!quit_) {
        // 调用epoll_wait 获取活动的事件并分配线程进行后处理
        activeChannel.clear();
        activeChannel = epoller_->epoll();
        for (auto &it : activeChannel) {
            // eventHandling_ = true; TODO  这个有什么用
            // 调用每个channel的处理函数
            it->handleEvents();
        }
        doPendingFunctors();
        // 处理连接失效时间
        epoller_->handleExpired();
    }
    looping_ = false;
}

void EventLoop::quit()
{
    quit_ = true;
    //  假如当前线程挂起，唤醒线程，执行loop, 然后退出
    if (!isInLoopThread()) {
        // 唤醒线程，Linux 有三种方式，自带的eventfd，管道，socketpair
        // 这里采用第一种 eventfd
        WakeUp();
    }
}

// 读出字节
void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = read(wakeupFd_, &one, sizeof(one));
    if (n < 0 || n != 1) {
        perror("read error");
    }
}

void EventLoop::WakeUp()
{
    // 往eventfd写入一个字节
    uint64_t one = 1;
    // int32_t n = sockets::write(wakeupFd_, &one, sizeof(one));
    // ::write(sockfd, buf, count);
    ssize_t n = write(wakeupFd_, &one, sizeof(one));// 可以考虑换成 socket专用的 send recv
    if (n < 0 || n != 1) {
        perror("write error");
    }
}

void EventLoop::shutdown(std::shared_ptr<Channel> channel) { 
    int fd = channel->getFd(); // 前置声明 此时不能使用方法
    ::shutdown(fd, SHUT_WR);
}

void EventLoop::handleConnect() {
  // poller_->epoll_mod(wakeupFd_, pwakeupChannel_, (EPOLLIN | EPOLLET |
  // EPOLLONESHOT), 0);
  epollMod(wakeupChannel_, 0);
}