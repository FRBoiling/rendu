//
// Created by boil on 18-10-3.
//

// the configured options and settings for Tutorial
#define VERSION_MAJOR 1
#define VERSION_MINOR 0

// 内存分配器
/* #undef USE_JEMALLOC */
#define USE_TCMALLOC

//string
#define RENDU_STD_STRING

//log
#define RENDU_TRACE
#define RENDU_DEBUG

//thread
#define CHECK_PTHREAD_RETURN_VALUE
