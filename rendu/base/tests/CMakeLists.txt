
add_executable(asynclogger_test AsyncLogger_test.cc)
target_link_libraries(asynclogger_test rendu_base)
add_test(NAME asynclogger_test COMMAND asynclogger_test)

add_executable(atomic_unittest Atomic_unittest.cc)
add_test(NAME atomic_unittest COMMAND atomic_unittest)

add_executable(logfile_test LogFile_test.cc)
target_link_libraries(logfile_test rendu_base)

add_executable(logger_test Logger_test.cc)
target_link_libraries(logger_test rendu_base)

add_executable(logstream_bench LogStream_bench.cc)
target_link_libraries(logstream_bench rendu_base)

if(BOOSTTEST_LIBRARY)
add_executable(logstream_test LogStream_test.cc)
target_link_libraries(logstream_test rendu_base boost_unit_test_framework)
add_test(NAME logstream_test COMMAND logstream_test)
endif()