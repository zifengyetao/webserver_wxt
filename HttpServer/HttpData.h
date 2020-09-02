#pragma once
#include <memory>
#include "Timer.h"
#include <string>
#include <map>
#include <unordered_map>
#include <sys/epoll.h>
#include <unistd.h>

class EventLoop;
class Channel;
class TimerNode;

enum ConnectionState { H_CONNECTED = 0, H_DISCONNECTING, H_DISCONNECTED };

enum HttpMethod { METHOD_POST = 1, METHOD_GET, METHOD_HEAD };

enum HttpVersion { HTTP_10 = 1, HTTP_11 };

enum ProcessState {
  STATE_PARSE_URI = 1,
  STATE_PARSE_HEADERS,
  STATE_RECV_BODY,
  STATE_ANALYSIS,
  STATE_FINISH
};

enum URIState {
  PARSE_URI_AGAIN = 1,
  PARSE_URI_ERROR,
  PARSE_URI_SUCCESS,
};

enum HeaderState {
  PARSE_HEADER_SUCCESS = 1,
  PARSE_HEADER_AGAIN,
  PARSE_HEADER_ERROR
};

enum AnalysisState { ANALYSIS_SUCCESS = 1, ANALYSIS_ERROR };

enum ParseState {
  H_START = 0,
  H_KEY,
  H_COLON,
  H_SPACES_AFTER_COLON,
  H_VALUE,
  H_CR,
  H_LF,
  H_END_CR,
  H_END_LF
};

class MimeType {
 private:
  static void init();
  static std::unordered_map<std::string, std::string> mime;
  MimeType();
  ~MimeType();

 public:
  static std::string getMime(const std::string &suffix);

 private:
  static pthread_once_t once_control;
};

// enable_shared_from_this 是一个以其派生类为模板类型参数的基类模板，继承它，派生类的this指针就能变成一个 shared_ptr
class HttpData : public std::enable_shared_from_this<HttpData>
{
public:
    // 构造函数启动loop循环，同时绑定回调
    HttpData(EventLoop* loop, int connfd);
    ~HttpData();

    void handleClose();
    void newEvent();
    void seperateTimer(); // TODO 这个啥意思
    // 考虑一下为什么不用const &，对象生命周期？
    void linkTimer(std::shared_ptr<TimerNode> mtimer) {
        timer_ = mtimer;
    }

    std::shared_ptr<Channel> getChannel() { return channel_; }
    EventLoop *getLoop() { return loop_; }
    
    void reset();
private:
    // 每个httpData 都含有一个EventLoop 和 一个Channel
    EventLoop* loop_;
    std::shared_ptr<Channel> channel_;
    int fd_;
    bool error_; // TODO 表示当前连接是否发生错误
    ConnectionState connectionState_; // 连接状态
    HttpMethod method_;
    HttpVersion HTTPVersion_;
    int nowReadPos_; // 当前解析位置索引？
    ProcessState state_;
    ParseState hState_; // TODO 解析状态？
    bool keepAlive_;
    // HTTP 头
    std::map<std::string, std::string> headers_;
    // 定时器
    std::weak_ptr<TimerNode> timer_;
    // 输入输出缓存
    std::string inBuffer_;
    std::string outBuffer_;

    std::string fileName_; // 文件名
    std::string path_;  // 文件路径

    // 核心就是这三个处理函数
    void handleRead();
    void handleWrite();
    void handleConn();
    void handleError(int fd, int err_num, std::string short_msg);

    URIState parseURI();
    HeaderState parseHeaders();
    AnalysisState analysisRequest();
};