#include "EventLoop.h"
#include "Server.h"

int main(int argc, char *argv[])
{
    int threadNum = 4;
    int port = 80;
    // 创建主线程，用于监听事件
    EventLoop loop;
    Server myHttpServer(&loop, threadNum, port);

    myHttpServer.start();
    loop.loop();
    return 0;
}