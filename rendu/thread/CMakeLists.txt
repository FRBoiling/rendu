aux_source_directory(. DIR_THREAD)
# 生成链接库
add_library (rendu_thread ${DIR_THREAD})

target_link_libraries(rendu_thread rendu_common)
target_link_libraries(rendu_thread rendu_log)
target_link_libraries(rendu_thread rendu_time)
target_link_libraries(rendu_thread pthread rt)
