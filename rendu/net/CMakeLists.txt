aux_source_directory(. DIR_NET)
# 生成链接库
add_library (rendu_net ${DIR_NET})

target_link_libraries(rendu_net rendu_common)
target_link_libraries(rendu_net rendu_time)
target_link_libraries(rendu_net rendu_thread)
target_link_libraries(rendu_net rendu_util)