#include "Timer.h"
#include <sys/time.h>

TimerNode::TimerNode(std::shared_ptr<HttpData> requestData, int timeout)
    : deleted_(false), httpReq(requestData) {
  struct timeval now;
  gettimeofday(&now, NULL);
  // 以毫秒计
  expiredTime_ =
      (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

TimerNode::~TimerNode() {
  if (httpReq) httpReq->handleClose();
}

TimerNode::TimerNode(TimerNode &tn)
    : httpReq(tn.httpReq), expiredTime_(0) {}

void TimerNode::update(int timeout) {
  struct timeval now;
  gettimeofday(&now, NULL);
  expiredTime_ =
      (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool TimerNode::isValid() {
  struct timeval now;
  gettimeofday(&now, NULL);
  size_t temp = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));
  if (temp < expiredTime_)
    return true;
  else {
    this->setDeleted();
    return false;
  }
}

void TimerNode::clearReq() {
  httpReq.reset();
  this->setDeleted();
}

void TimerManager::addTimer(std::shared_ptr<HttpData> httpReq, int timeout)
{
    SPTimerNode new_node(new TimerNode(httpReq, timeout));
    timerNodeQueue_.push(new_node);
    httpReq->linkTimer(new_node);
}

void TimerManager::handleExpiredEvent() {
  while (!timerNodeQueue_.empty()) {
    SPTimerNode ptimer_now = timerNodeQueue_.top();
    if (ptimer_now->isDeleted())
      timerNodeQueue_.pop();
    else if (!ptimer_now->isValid())
      timerNodeQueue_.pop();
    else
      break;
  }
}

TimerManager::TimerManager() 
{
}

TimerManager::~TimerManager() 
{
}