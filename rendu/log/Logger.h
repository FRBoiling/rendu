//
// Created by boil on 18-10-3.
//

#ifndef RENDU_LOG_LOGGER_H
#define RENDU_LOG_LOGGER_H

#include "LogImpl.h"

namespace rendu {
    namespace log {

        class Logger {
        public:
            Logger(SourceFile file, int line);
            Logger(SourceFile file, int line, LogLevel level);
            Logger(SourceFile file, int line, LogLevel level, const char* func);
            Logger(SourceFile file, int line, bool toAbort);
            ~Logger();

            LogStream& stream() { return log_impl_.stream_; }

            static LogLevel logLevel();
            static void setLogLevel(LogLevel level);

            typedef void (*OutputFunc)(const char* msg, int len);
            typedef void (*FlushFunc)();
            static void setOutput(OutputFunc);
            static void setFlush(FlushFunc);
//            static void setTimeZone(const TimeZone& tz);

        private:
            LogImpl log_impl_;
        };

    }
}

#endif //RENDU_LOG_LOGGER_H
