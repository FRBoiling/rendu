aux_source_directory(. DIR_COMMON)
# 生成链接库
add_library (rendu_common ${DIR_COMMON})

target_link_libraries(rendu_common rendu_util)