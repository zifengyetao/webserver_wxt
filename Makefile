# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /wxt/webServer_wxt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /wxt/webServer_wxt

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/local/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /wxt/webServer_wxt/CMakeFiles /wxt/webServer_wxt/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /wxt/webServer_wxt/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named httpserver

# Build rule for target.
httpserver: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 httpserver
.PHONY : httpserver

# fast build rule for target.
httpserver/fast:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/build
.PHONY : httpserver/fast

HttpServer/Channel.o: HttpServer/Channel.cpp.o

.PHONY : HttpServer/Channel.o

# target to build an object file
HttpServer/Channel.cpp.o:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Channel.cpp.o
.PHONY : HttpServer/Channel.cpp.o

HttpServer/Channel.i: HttpServer/Channel.cpp.i

.PHONY : HttpServer/Channel.i

# target to preprocess a source file
HttpServer/Channel.cpp.i:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Channel.cpp.i
.PHONY : HttpServer/Channel.cpp.i

HttpServer/Channel.s: HttpServer/Channel.cpp.s

.PHONY : HttpServer/Channel.s

# target to generate assembly for a file
HttpServer/Channel.cpp.s:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Channel.cpp.s
.PHONY : HttpServer/Channel.cpp.s

HttpServer/Epoll.o: HttpServer/Epoll.cpp.o

.PHONY : HttpServer/Epoll.o

# target to build an object file
HttpServer/Epoll.cpp.o:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Epoll.cpp.o
.PHONY : HttpServer/Epoll.cpp.o

HttpServer/Epoll.i: HttpServer/Epoll.cpp.i

.PHONY : HttpServer/Epoll.i

# target to preprocess a source file
HttpServer/Epoll.cpp.i:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Epoll.cpp.i
.PHONY : HttpServer/Epoll.cpp.i

HttpServer/Epoll.s: HttpServer/Epoll.cpp.s

.PHONY : HttpServer/Epoll.s

# target to generate assembly for a file
HttpServer/Epoll.cpp.s:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Epoll.cpp.s
.PHONY : HttpServer/Epoll.cpp.s

HttpServer/EventLoop.o: HttpServer/EventLoop.cpp.o

.PHONY : HttpServer/EventLoop.o

# target to build an object file
HttpServer/EventLoop.cpp.o:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/EventLoop.cpp.o
.PHONY : HttpServer/EventLoop.cpp.o

HttpServer/EventLoop.i: HttpServer/EventLoop.cpp.i

.PHONY : HttpServer/EventLoop.i

# target to preprocess a source file
HttpServer/EventLoop.cpp.i:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/EventLoop.cpp.i
.PHONY : HttpServer/EventLoop.cpp.i

HttpServer/EventLoop.s: HttpServer/EventLoop.cpp.s

.PHONY : HttpServer/EventLoop.s

# target to generate assembly for a file
HttpServer/EventLoop.cpp.s:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/EventLoop.cpp.s
.PHONY : HttpServer/EventLoop.cpp.s

HttpServer/EventLoopThread.o: HttpServer/EventLoopThread.cpp.o

.PHONY : HttpServer/EventLoopThread.o

# target to build an object file
HttpServer/EventLoopThread.cpp.o:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/EventLoopThread.cpp.o
.PHONY : HttpServer/EventLoopThread.cpp.o

HttpServer/EventLoopThread.i: HttpServer/EventLoopThread.cpp.i

.PHONY : HttpServer/EventLoopThread.i

# target to preprocess a source file
HttpServer/EventLoopThread.cpp.i:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/EventLoopThread.cpp.i
.PHONY : HttpServer/EventLoopThread.cpp.i

HttpServer/EventLoopThread.s: HttpServer/EventLoopThread.cpp.s

.PHONY : HttpServer/EventLoopThread.s

# target to generate assembly for a file
HttpServer/EventLoopThread.cpp.s:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/EventLoopThread.cpp.s
.PHONY : HttpServer/EventLoopThread.cpp.s

HttpServer/EventLoopThreadPool.o: HttpServer/EventLoopThreadPool.cpp.o

.PHONY : HttpServer/EventLoopThreadPool.o

# target to build an object file
HttpServer/EventLoopThreadPool.cpp.o:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/EventLoopThreadPool.cpp.o
.PHONY : HttpServer/EventLoopThreadPool.cpp.o

HttpServer/EventLoopThreadPool.i: HttpServer/EventLoopThreadPool.cpp.i

.PHONY : HttpServer/EventLoopThreadPool.i

# target to preprocess a source file
HttpServer/EventLoopThreadPool.cpp.i:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/EventLoopThreadPool.cpp.i
.PHONY : HttpServer/EventLoopThreadPool.cpp.i

HttpServer/EventLoopThreadPool.s: HttpServer/EventLoopThreadPool.cpp.s

.PHONY : HttpServer/EventLoopThreadPool.s

# target to generate assembly for a file
HttpServer/EventLoopThreadPool.cpp.s:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/EventLoopThreadPool.cpp.s
.PHONY : HttpServer/EventLoopThreadPool.cpp.s

HttpServer/HttpData.o: HttpServer/HttpData.cpp.o

.PHONY : HttpServer/HttpData.o

# target to build an object file
HttpServer/HttpData.cpp.o:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/HttpData.cpp.o
.PHONY : HttpServer/HttpData.cpp.o

HttpServer/HttpData.i: HttpServer/HttpData.cpp.i

.PHONY : HttpServer/HttpData.i

# target to preprocess a source file
HttpServer/HttpData.cpp.i:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/HttpData.cpp.i
.PHONY : HttpServer/HttpData.cpp.i

HttpServer/HttpData.s: HttpServer/HttpData.cpp.s

.PHONY : HttpServer/HttpData.s

# target to generate assembly for a file
HttpServer/HttpData.cpp.s:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/HttpData.cpp.s
.PHONY : HttpServer/HttpData.cpp.s

HttpServer/Server.o: HttpServer/Server.cpp.o

.PHONY : HttpServer/Server.o

# target to build an object file
HttpServer/Server.cpp.o:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Server.cpp.o
.PHONY : HttpServer/Server.cpp.o

HttpServer/Server.i: HttpServer/Server.cpp.i

.PHONY : HttpServer/Server.i

# target to preprocess a source file
HttpServer/Server.cpp.i:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Server.cpp.i
.PHONY : HttpServer/Server.cpp.i

HttpServer/Server.s: HttpServer/Server.cpp.s

.PHONY : HttpServer/Server.s

# target to generate assembly for a file
HttpServer/Server.cpp.s:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Server.cpp.s
.PHONY : HttpServer/Server.cpp.s

HttpServer/Timer.o: HttpServer/Timer.cpp.o

.PHONY : HttpServer/Timer.o

# target to build an object file
HttpServer/Timer.cpp.o:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Timer.cpp.o
.PHONY : HttpServer/Timer.cpp.o

HttpServer/Timer.i: HttpServer/Timer.cpp.i

.PHONY : HttpServer/Timer.i

# target to preprocess a source file
HttpServer/Timer.cpp.i:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Timer.cpp.i
.PHONY : HttpServer/Timer.cpp.i

HttpServer/Timer.s: HttpServer/Timer.cpp.s

.PHONY : HttpServer/Timer.s

# target to generate assembly for a file
HttpServer/Timer.cpp.s:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/Timer.cpp.s
.PHONY : HttpServer/Timer.cpp.s

HttpServer/main.o: HttpServer/main.cpp.o

.PHONY : HttpServer/main.o

# target to build an object file
HttpServer/main.cpp.o:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/main.cpp.o
.PHONY : HttpServer/main.cpp.o

HttpServer/main.i: HttpServer/main.cpp.i

.PHONY : HttpServer/main.i

# target to preprocess a source file
HttpServer/main.cpp.i:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/main.cpp.i
.PHONY : HttpServer/main.cpp.i

HttpServer/main.s: HttpServer/main.cpp.s

.PHONY : HttpServer/main.s

# target to generate assembly for a file
HttpServer/main.cpp.s:
	$(MAKE) -f CMakeFiles/httpserver.dir/build.make CMakeFiles/httpserver.dir/HttpServer/main.cpp.s
.PHONY : HttpServer/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... httpserver"
	@echo "... HttpServer/Channel.o"
	@echo "... HttpServer/Channel.i"
	@echo "... HttpServer/Channel.s"
	@echo "... HttpServer/Epoll.o"
	@echo "... HttpServer/Epoll.i"
	@echo "... HttpServer/Epoll.s"
	@echo "... HttpServer/EventLoop.o"
	@echo "... HttpServer/EventLoop.i"
	@echo "... HttpServer/EventLoop.s"
	@echo "... HttpServer/EventLoopThread.o"
	@echo "... HttpServer/EventLoopThread.i"
	@echo "... HttpServer/EventLoopThread.s"
	@echo "... HttpServer/EventLoopThreadPool.o"
	@echo "... HttpServer/EventLoopThreadPool.i"
	@echo "... HttpServer/EventLoopThreadPool.s"
	@echo "... HttpServer/HttpData.o"
	@echo "... HttpServer/HttpData.i"
	@echo "... HttpServer/HttpData.s"
	@echo "... HttpServer/Server.o"
	@echo "... HttpServer/Server.i"
	@echo "... HttpServer/Server.s"
	@echo "... HttpServer/Timer.o"
	@echo "... HttpServer/Timer.i"
	@echo "... HttpServer/Timer.s"
	@echo "... HttpServer/main.o"
	@echo "... HttpServer/main.i"
	@echo "... HttpServer/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
