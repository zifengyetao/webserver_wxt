#pragma once
#include <vector>
#include <memory>
#include <sys/epoll.h>
#include "Channel.h"
#include "HttpData.h"

class Epoll
{
public:
    Epoll();
    ~Epoll();

    void epollAdd(std::shared_ptr<Channel> channel, int timeout);
    void epollMod(std::shared_ptr<Channel> channel, int timeout);
    void epollDel(std::shared_ptr<Channel> channel);

    void addTimer(std::shared_ptr<Channel> channel, int timeout);

    // 返回活跃事件列表
    std::vector<std::shared_ptr<Channel>> epoll();

    // 分发处理函数
    std::vector<std::shared_ptr<Channel>> getEventsRequest(int events_num);

    void handleExpired() {
        timerManager_.handleExpiredEvent();
    }
private:
    static constexpr int MAXFDS = 100000;

    int epollFd_;
    std::vector<epoll_event> activeEvents_; // 保存活跃事件
    std::shared_ptr<Channel> fd2chan_[MAXFDS]; // 保存监听事件对应的channel  
    std::shared_ptr<HttpData> fd2http_[MAXFDS]; // 保存所有Http连接 后面考虑用map存储channel和httpdata
    TimerManager timerManager_;
};