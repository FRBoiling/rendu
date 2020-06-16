##添加函数检查功能
#include(CheckFunctionExists)
##检查系统是否支持accpet4，将检查结果设置至HAVE_ACCEPT4
#check_function_exists(accept4 HAVE_ACCEPT4)
#if(NOT HAVE_ACCEPT4)
#    set_source_files_properties(SocketsOps.cc PROPERTIES COMPILE_FLAGS "-DNO_ACCEPT4")
#endif()
#set(net_SRCS
#        Acceptor.cc
#        Buffer.cc
#        Channel.cc
#        Connector.cc
#        EventLoop.cc
#        EventLoopThread.cc
#        EventLoopThreadPool.cc
#        InetAddress.cc
#        Poller.cc
#        poller/DefaultPoller.cc
#        poller/EPollPoller.cc
#        poller/PollPoller.cc
#        Socket.cc
#        SocketsOps.cc
#        TcpClient.cc
#        TcpConnection.cc
#        TcpServer.cc
#        Timer.cc
#        TimerQueue.cc
#        )

# FILE (GLOB NET_SOURCES "*.cc" "*.c" "./poller/*.cc" )
# FILE (GLOB NET_INCLUDES "*.h" "*.h" "./poller/*.h"  "./AFolder/*.h" )

FILE(GLOB NET_SOURCES "sources/*.cc") 
FILE(GLOB NET_INCLUDES "includes/*.h" "*.h") 

SET (DIR_NET
        ${NET_SOURCES}
        ${NET_INCLUDES}
        )

aux_source_directory(. DIR_NET)
# 生成链接库
add_library (rendu_net ${DIR_NET})
target_link_libraries(rendu_net rendu_base)
# install(TARGETS rendu_net DESTINATION lib)

#set(HEADERS
#        Buffer.h
#        Callbacks.h
#        Channel.h
#        Endian.h
#        EventLoop.h
#        EventLoopThread.h
#        EventLoopThreadPool.h
#        InetAddress.h
#        TcpClient.h
#        TcpConnection.h
#        TcpServer.h
#        TimerId.h
#        )
#install(FILES ${HEADERS} DESTINATION include/rendu/net)
