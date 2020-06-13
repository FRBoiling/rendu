FILE(GLOB BASE_SOURCES "sources/*.cc") 
FILE(GLOB BASE_INCLUDES "includes/*.h") 

# FILE (GLOB BASE_SOURCES "*.cc" "*.c")
# FILE (GLOB BASE_INCLUDES "*.h" "*.h")

SET (DIR_BASE
        ${BASE_SOURCES}
        ${BASE_INCLUDES}
        )

aux_source_directory(. DIR_BASE)
# 生成链接库
add_library (rendu_base ${DIR_BASE})
target_link_libraries(rendu_base rendu_zmalloc)