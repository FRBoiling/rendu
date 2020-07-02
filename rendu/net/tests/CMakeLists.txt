add_executable(channel_test Channel_test.cc)
target_link_libraries(channel_test rendu_net)

add_executable(echoserver_unittest EchoServer_unittest.cc)
target_link_libraries(echoserver_unittest rendu_net)

add_executable(echoclient_unittest EchoClient_unittest.cc)
target_link_libraries(echoclient_unittest rendu_net)

add_executable(eventloop_unittest EventLoop_unittest.cc)
target_link_libraries(eventloop_unittest rendu_net)

add_executable(eventloopthread_unittest EventLoopThread_unittest.cc)
target_link_libraries(eventloopthread_unittest rendu_net)

add_executable(eventloopthreadpool_unittest EventLoopThreadPool_unittest.cc)
target_link_libraries(eventloopthreadpool_unittest rendu_net)

# if(BOOSTTEST_LIBRARY)
# add_executable(buffer_unittest Buffer_unittest.cc)
# target_link_libraries(buffer_unittest rendu_net boost_unit_test_framework)
# add_test(NAME buffer_unittest COMMAND buffer_unittest)

# add_executable(inetaddress_unittest InetAddress_unittest.cc)
# target_link_libraries(inetaddress_unittest rendu_net boost_unit_test_framework)
# add_test(NAME inetaddress_unittest COMMAND inetaddress_unittest)

# endif()

add_executable(tcpclient_reg1 TcpClient_reg1.cc)
target_link_libraries(tcpclient_reg1 rendu_net)

add_executable(tcpclient_reg2 TcpClient_reg2.cc)
target_link_libraries(tcpclient_reg2 rendu_net)

add_executable(tcpclient_reg3 TcpClient_reg3.cc)
target_link_libraries(tcpclient_reg3 rendu_net)

add_executable(timerqueue_unittest TimerQueue_unittest.cc)
target_link_libraries(timerqueue_unittest rendu_net)
add_test(NAME timerqueue_unittest COMMAND timerqueue_unittest)

