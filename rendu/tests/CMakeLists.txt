#log unittest
add_executable(log_test log/log_test.cc)
target_link_libraries(log_test rendu_log)

add_executable(logfile_test log/logfile_test.cc)
target_link_libraries(logfile_test rendu_log)

add_executable(logstream_test log/logstream_test.cc)
target_link_libraries(logstream_test rendu_log)

add_executable(asynclogger_test log/asynclogger_test.cc)
target_link_libraries(asynclogger_test rendu_log)

#time unittest
add_executable(timestamp_test time/timestamp_test.cc)
target_link_libraries(timestamp_test rendu_time)

add_executable(timezone_test time/timezone_test.cc)
target_link_libraries(timezone_test rendu_time)

#thread unittest
add_executable(thread_test thread/thread_test.cc)
target_link_libraries(thread_test rendu_time)
target_link_libraries(thread_test rendu_thread)

add_executable(thread_bench thread/thread_bench.cc)
target_link_libraries(thread_bench rendu_time)
target_link_libraries(thread_bench rendu_thread)

add_executable(mutex_test thread/mutex_test.cc)
target_link_libraries(mutex_test rendu_time)
target_link_libraries(mutex_test rendu_thread)

