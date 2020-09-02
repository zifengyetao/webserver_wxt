cmake_minimum_required(VERSION 2.6)

project (WXT_WEBSERVER)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -O0 -Wno-unused-variable -pthread")

set(httpServer_srcs 
HttpServer/Channel.cpp
HttpServer/Epoll.cpp
HttpServer/EventLoop.cpp
HttpServer/EventLoopThread.cpp
HttpServer/EventLoopThreadPool.cpp
HttpServer/HttpData.cpp
HttpServer/Server.cpp
HttpServer/Timer.cpp
HttpServer/main.cpp
)

add_executable(httpserver ${httpServer_srcs})
#光包含库目录是没用的，还必须使用TARGET_LINK_LIBRARIES链接该库
TARGET_LINK_LIBRARIES(httpserver)