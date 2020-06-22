
add_executable(asynclogger_test AsyncLogger_test.cc)
target_link_libraries(asynclogger_test rendu_base)
add_test(NAME asynclogger_test COMMAND asynclogger_test)

add_executable(atomic_unittest Atomic_unittest.cc)
add_test(NAME atomic_unittest COMMAND atomic_unittest)

