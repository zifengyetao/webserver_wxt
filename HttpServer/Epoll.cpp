#include "Epoll.h"
#include "assert.h"
#include <iostream>
#include <string.h>

using namespace std;

constexpr int EPOLLWAIT_TIME = 10000; // 阻塞10000ms
const int EVENTSNUM = 4096;

Epoll::Epoll():
    epollFd_(epoll_create(1)),
    activeEvents_(EVENTSNUM)
{
    assert(epollFd_ > 0);
}

Epoll::~Epoll()
{
}

// 添加/注册事件到内核事件表
void Epoll::epollAdd(std::shared_ptr<Channel> channel, int timeout)
{
    int fd = channel->getFd();
    // 定时器，每个http连接对应一个loop，对应一个channel，对应一个线程
    // 需要为每个http连接设置一个超时时间
    if (timeout > 0) {
        addTimer(channel, timeout);
        fd2http_[fd] = channel->getHolder(); // 获取每个channel对应的HTTP连接 
    }
    
    uint32_t events = channel->getEvents();

    epoll_event event;
    event.events = events;
    event.data.fd = fd;

    channel->EqualAndUpdateLastEvent();
    
    fd2chan_[fd] = channel;
    if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &event) == -1) {
        cout << "epoll_ctl error" << endl;
        fd2chan_[fd].reset();
    }
}

// 添加/注册事件到内核事件表
void Epoll::epollMod(std::shared_ptr<Channel> channel, int timeout)
{
    if (timeout > 0) {
        addTimer(channel, timeout);
    }
    // 看监听事件类型是否变更，若没有变更，无需重新挂到内核事件表
    if (channel->EqualAndUpdateLastEvent()) {
        return;
    }
    
    int fd = channel->getFd();
    uint32_t events = channel->getEvents();

    epoll_event event;
    event.events = events;
    event.data.fd = fd;

    // fd2chan_[fd] = channel; TODO 为什么不更新
    if (epoll_ctl(epollFd_, EPOLL_CTL_MOD, fd, &event) == -1) {
        cout << "epoll_ctl error" << endl;
        fd2chan_[fd].reset();
    }
}

// 添加/注册事件到内核事件表
void Epoll::epollDel(std::shared_ptr<Channel> channel)
{
    int fd = channel->getFd();
    uint32_t events = channel->getEvents();

    epoll_event event;
    event.events = events;
    event.data.fd = fd;

    if (epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, &event) == -1) {
        cout << "epoll_ctl error" << endl;
    }

    fd2chan_[fd].reset();
    fd2http_[fd].reset();
}

std::vector<std::shared_ptr<Channel>> Epoll::epoll()
{
    // 调用epoll_wait 获取活动的事件数
    int nReady = epoll_wait(epollFd_, &*activeEvents_.begin(), activeEvents_.size(), EPOLLWAIT_TIME);
    if (nReady < 0) {
        perror("epoll wait error"); // EINTER
    } else {
        cout << "epoll wait success" << endl;
    }
    
    std::vector<std::shared_ptr<Channel>> validChannnel = getEventsRequest(nReady);
    if (validChannnel.size() > 0) {
        return validChannnel;
    }
    return validChannnel;
}

std::vector<std::shared_ptr<Channel>> Epoll::getEventsRequest(int events_num)
{
    std::vector<std::shared_ptr<Channel>> req_data;
    for (int i = 0; i < events_num; ++i) {
        int fd = activeEvents_[i].data.fd;
        std::shared_ptr<Channel> channel = fd2chan_[fd]; // 根据触发事件的fd，确定channel，并更新收到的revents；

        if (!channel) {
            cout << " getEventsRequest error" << endl;
            continue;
        }
        channel->setRevents(activeEvents_[i].events); 
        channel->setEvents(0); // TODO 为啥 接收到事件通知的时候，暂时还不确定是要挂读事件还是写事件
        req_data.push_back(channel);
    }
    return req_data;
}

void Epoll::addTimer(std::shared_ptr<Channel> channel, int timeout) {
  std::shared_ptr<HttpData> t = channel->getHolder();
  if (t)
    timerManager_.addTimer(t, timeout);
  else
    cout << "timer add fail";
}
