#pragma once
#include <memory>
#include <functional>

class EventLoop;
class HttpData;

class Channel
{
public:
    using CallBack = std::function<void()>;

    Channel(EventLoop *loop);
    Channel(EventLoop * eventloop, int fd);
    ~Channel();

    int getFd() {
        return fd_;
    }

    void setFd(int fd) {
        fd_ = fd;
    }

    uint32_t &getEvents() {
        return events_;
    }

    uint32_t getRevents() {
        return revents_;
    }

    void setEvents(int events) {
        events_ = events;
    }

    void setRevents(int revents) {
        revents_ = revents;
    }

    // 更新最新的事件类型 TODO 考虑是否多余，直接用events_判读是否可以，如果不可以，函数考虑拆分
    bool EqualAndUpdateLastEvent() {
        if (lastEvents_ == events_) {
            return true;
        }
        lastEvents_ = events_;
        return false;
    }

    // 每个channel的回调->每个事件的处理包括可读 可写 连接  断开
    void handleRead();
    void handleWrite();
    void handleError();
    void handleConnect(); // 连接的处理 包括连接和断开 非为监听端口的处理（新连接到来） 和 已连接事件可读事件的触发

    void handleEvents();

    void setReadCallBack(CallBack readCallBack) {
        ReadCallBack_ = readCallBack;
    }

    void setWriteCallBack(CallBack writeCallBack) {
        WriteCallBack_ = writeCallBack;
    }
    
    void setErrorCallBack(CallBack ErrorCallBack) {
        ErrorReadCallBack_ = ErrorCallBack;
    }

    void setConnectCallBack(CallBack connectCallBack) {
        ConnectCallBack_ = connectCallBack;
    }

    void setHolder(std::shared_ptr<HttpData> holder) { holder_ = holder; }
    std::shared_ptr<HttpData> getHolder() {
        std::shared_ptr<HttpData> ret(holder_.lock());
        return ret;
    }
private:
    EventLoop *loop_;
    int fd_; // channel对应的事件fd
    uint32_t events_; // 监听事件 events属性为POLLIN|POLLOUT, 比如返回的事件revents为POLLIN，则为可读事件
    uint32_t revents_;// 收到的触发事件 it's the received event types of epoll or poll
    uint32_t lastEvents_; // 最新的监听事件属性，用于判断是否需要更新内核事件表的监听事件，如mod操作将事件更新为可读事件，若已经是监听可读事件，则无需操作
    std::weak_ptr<HttpData> holder_; // HttpData 连接可能断开，主动释放，因此需要用weak_ptr, 不能用shared_ptr

    CallBack ReadCallBack_;
    CallBack WriteCallBack_;
    CallBack ErrorReadCallBack_;
    CallBack ConnectCallBack_;
};