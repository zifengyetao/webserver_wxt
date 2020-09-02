#pragma once
// 每个http请求的有效时间，失效时间，定时器
#include "HttpData.h"
// #include <deque>
#include <memory>
#include <queue>

class HttpData;
// 单个定时器类，包含http对象，失效时间
class TimerNode
{
public:
    TimerNode(std::shared_ptr<HttpData> requestData, int timeout);
    ~TimerNode();
    TimerNode(TimerNode &tn);

    size_t getExpTime() {
        return expiredTime_;
    }

    void update(int timeout);
    bool isValid();
    void clearReq();
    void setDeleted() { deleted_ = true; }
    bool isDeleted() const { return deleted_; }
private:
    bool deleted_ {false};
    size_t expiredTime_;
    std::shared_ptr<HttpData> httpReq;
};

struct TimerCmp {
  bool operator()(std::shared_ptr<TimerNode> &a,
                  std::shared_ptr<TimerNode> &b) const {
    return a->getExpTime() > b->getExpTime();
  }
};

// 定时器管理类，管理多个http请求的定时器对象
class TimerManager
{
public:
    TimerManager();
    ~TimerManager();

    void addTimer(std::shared_ptr<HttpData> httpReq, int timeout); // 代表每个http请求的超时时间
    void handleExpiredEvent();
private:
    using SPTimerNode = std::shared_ptr<TimerNode>;
    std::priority_queue<SPTimerNode, std::deque<SPTimerNode>, TimerCmp> timerNodeQueue_;
};