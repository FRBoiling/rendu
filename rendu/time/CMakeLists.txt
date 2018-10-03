aux_source_directory(. DIR_TIME)
# 生成链接库
add_library (rendu_time ${DIR_TIME})

target_link_libraries(rendu_time rendu_common)
