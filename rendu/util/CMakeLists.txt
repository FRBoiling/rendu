aux_source_directory(. DIR_LOG)
# 生成链接库
add_library (rendu_util ${DIR_LOG})

target_link_libraries(rendu_util rendu_common)
target_link_libraries(rendu_util rendu_time)
target_link_libraries(rendu_util rendu_thread)