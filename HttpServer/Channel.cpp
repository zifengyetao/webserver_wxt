// channel cpp
#include "Channel.h"
#include <sys/epoll.h>

Channel::Channel(EventLoop *loop)
    : loop_(loop), fd_(0), events_(0), revents_(0), lastEvents_(0){}

Channel::Channel(EventLoop * eventloop, int fd):
    loop_(eventloop),
    fd_(fd) {}

Channel::~Channel() {}

void Channel::handleRead()
{
    ReadCallBack_();
}

void Channel::handleWrite()
{
    WriteCallBack_();
}

void Channel::handleError()
{
    ErrorReadCallBack_();
}

void Channel::handleConnect()
{
    ConnectCallBack_();
}

void Channel::handleEvents()
{
    // 假如是正常关闭事件 不处理
    if (revents_ & EPOLLRDHUP && !(revents_ & EPOLLIN)) {
        return;
    }
    // 假如对端发生异常 比如主动写的时候返回异常
    if (revents_ & EPOLLERR) {
        handleError();
        return;
    }

    // 假如是可读事件 或者带外数据 或者挂起
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLHUP)) {
        handleRead();
    }
    // 假如是可写事件
    if (revents_ & EPOLLOUT) {
        handleWrite();
    }

    handleConnect(); // TODO 为什么要处理一下连接事件 比如读完，重新挂起？
}