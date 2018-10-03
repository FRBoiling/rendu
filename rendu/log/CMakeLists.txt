aux_source_directory(. DIR_LOG)
# 生成链接库
add_library (rendu_log ${DIR_LOG})

target_link_libraries(rendu_log rendu_common)
target_link_libraries(rendu_log rendu_time)