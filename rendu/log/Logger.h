//
// Created by boil on 18-10-3.
//

#ifndef RENDU_LOG_LOGGER_H
#define RENDU_LOG_LOGGER_H

#include "LogImpl.h"
#include <rendu/time/TimeZone.h>

namespace rendu {
    namespace log {

        class Logger {
        public:
            Logger(SourceFile file, int line);

            Logger(SourceFile file, int line, LogLevel level);

            Logger(SourceFile file, int line, LogLevel level, const char *func);

            Logger(SourceFile file, int line, bool toAbort);

            ~Logger();

            LogStream &stream() { return log_impl_.stream_; }

            static void init();

            static LogLevel logLevel();

            static void setLogLevel(LogLevel level);

            typedef void (*OutputFunc)(const char *msg, int len);

            typedef void (*FlushFunc)();

            static void setOutput(OutputFunc);

            static void setFlush(FlushFunc);

            static void setTimeZone(const TimeZone &tz);

        private:
            LogImpl log_impl_;
        };


        //
// CAUTION: do not write:
//
// if (good)
//   LOG_INFO << "Good news";
// else
//   LOG_WARN << "Bad news";
//
// this expends to
//
// if (good)
//   if (logging_INFO)
//     logInfoStream << "Good news";
//   else
//     logWarnStream << "Bad news";
//
#define LOG_TRACE if (Logger::logLevel() <= TRACE) \
        Logger(__FILE__, __LINE__, TRACE, __func__).stream()
#define LOG_DEBUG if (Logger::logLevel() <= DEBUG) \
        Logger(__FILE__, __LINE__, DEBUG, __func__).stream()
#define LOG_INFO if (Logger::logLevel() <= INFO) \
        Logger(__FILE__, __LINE__).stream()

#define LOG_WARN Logger(__FILE__, __LINE__, WARN).stream()
#define LOG_ERROR Logger(__FILE__, __LINE__, ERROR).stream()
#define LOG_FATAL Logger(__FILE__, __LINE__,FATAL).stream()
#define LOG_SYSERR Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL Logger(__FILE__, __LINE__, true).stream()
    }
}

#endif //RENDU_LOG_LOGGER_H
