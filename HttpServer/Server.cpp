#include "Server.h"
#include "sys/socket.h"
#include <iostream>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/tcp.h>

int socket_listen_bind(int port)
{
    int listenFd = socket(AF_INET, SOCK_STREAM, 0); // IPV4 TCP
    if (listenFd < 0) {
        std::cout << "create socket error" << std::endl;
    }

    int reuse = 1;
    if (setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        std::cout << "setsockopt error" << std::endl;
        close(listenFd);
    }
    
    // 设置服务器IP和Port，和监听描述符绑定
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 监听所有地址
    server_addr.sin_port = htons((unsigned short)port);

    // 命名socket 
    if (bind(listenFd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cout << "bind error" << std::endl;
        close(listenFd);
    }

    if (listen(listenFd, 5) < 0) {
        std::cout << "listen error" << std::endl;
        close(listenFd);
    }

    if (listenFd < 0) {
        close(listenFd);
    }
    return listenFd;
}

int setSocketNonBlocking(int fd)
{
    int flag = fcntl(fd, F_GETFL);
    if (flag < 0) {
        return -1;
    }

    int ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
    if (ret < 0) {
        return -1;
    }
    return 0;
}

Server::Server(EventLoop* loop, int threadNum, int port):
    loop_(loop),
    acceptChannel_(new Channel(loop)), // 不指定fd TODO 为什么不先生成fd，然后直接构造函数绑定fd
    threadNum_(threadNum),
    threadPool_(new EventLoopThreadPool(loop, threadNum)),
    port_(port),
    listenFd_(socket_listen_bind(port_)) 
{   // 监听fd 由socket根据端口生成
    acceptChannel_->setFd(listenFd_);
    if (setSocketNonBlocking(listenFd_) < 0) {
        std::cout << "setSocketNonBlocking error" << std::endl;
        abort();
    }
}

Server::~Server() {}

void Server::start()
{
    // 根据threadNum 启动线程池 线程池的baseloop就是主线程的loop
    threadPool_->start(); // 实际每个线程创建一个EventLoop对象， EventLoop包括epoller和channel，创建epollcreate并调用loop，进而调用epollwait
    acceptChannel_->setEvents(EPOLLIN | EPOLLET); // 监听事件
    acceptChannel_->setReadCallBack(std::bind(&Server::handleNewConnect, this)); 
    acceptChannel_->setConnectCallBack(std::bind(&Server::handleThisConnect, this));
    // 挂到红黑树上
    loop_->epollAdd(acceptChannel_, 0);
    started_ = true;
}

void Server::handleNewConnect() {
  struct sockaddr_in client_addr;
  memset(&client_addr, 0, sizeof(struct sockaddr_in));
  socklen_t client_addr_len = sizeof(client_addr);
  int accept_fd = 0;
  while ((accept_fd = accept(listenFd_, (struct sockaddr *)&client_addr,
                             &client_addr_len)) > 0) {
    EventLoop *loop = threadPool_->getNextLoop();
    // LOG << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":"
    //     << ntohs(client_addr.sin_port);
    // cout << "new connection" << endl;
    // cout << inet_ntoa(client_addr.sin_addr) << endl;
    // cout << ntohs(client_addr.sin_port) << endl;
    /*
    // TCP的保活机制默认是关闭的
    int optval = 0;
    socklen_t len_optval = 4;
    getsockopt(accept_fd, SOL_SOCKET,  SO_KEEPALIVE, &optval, &len_optval);
    cout << "optval ==" << optval << endl;
    */
    // 限制服务器的最大并发连接数
    if (accept_fd >= MAXFDS) {
      close(accept_fd);
      continue;
    }
    // 设为非阻塞模式
    if (setSocketNonBlocking(accept_fd) < 0) {
    //   LOG << "Set non block failed!";
    //   // perror("Set non block failed!");
      return;
    }

    // 启动TCP_NODELAY，就意味着禁用了Nagle算法，允许小包的发送。对于延时敏感型，同时数据传输量比较小的应用，开启TCP_NODELAY选项无疑是一个正确的选择
    int enable = 1;
    setsockopt(accept_fd, IPPROTO_TCP, TCP_NODELAY, (void *)&enable, sizeof(enable));
    // setSocketNoLinger(accept_fd);

    std::shared_ptr<HttpData> req_info(new HttpData(loop, accept_fd));
    req_info->getChannel()->setHolder(req_info);
    // 工作线程也有监听事件吗？应该没有，但是每个工作线程都有一个epoll，都会epoll_wait, 其实对epoll来说不感知监听事件和非监听事件，只是回调函数不一样
    loop->queueInLoop(std::bind(&HttpData::newEvent, req_info));
  }
  acceptChannel_->setEvents(EPOLLIN | EPOLLET);
}