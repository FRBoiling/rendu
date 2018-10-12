//
// Created by boil on 18-10-3.
//

#include <rendu/time/TimeZone.h>
#include "Logger.h"

namespace rendu {
    namespace log {

        __thread char t_errnobuf[512];

        const char *strerror_tl(int savedErrno) {
            return strerror_r(savedErrno, t_errnobuf, sizeof t_errnobuf);
        }

        LogLevel initLogLevel();

        LogLevel g_logLevel = initLogLevel();

        LogLevel Logger::logLevel() {
            return g_logLevel;
        }

        LogLevel initLogLevel() {
//#ifdef defined(RENDU_LOG_TRACE)
//            return TRACE;
//#elif defined(RENDU_LOG_DEBUG)
//            return DEBUG;
//#else
//            return INFO;
//#endif
            if (::getenv("RENDU_LOG_TRACE"))
                return TRACE;
            else if (::getenv("RENDU_LOG_DEBUG"))
                return DEBUG;
            else
                return INFO;

        }

        //
        void defaultOutput(const char *msg, size_t len) {
            size_t n = fwrite(msg, 1, len, stdout);
            //FIXME check n
            (void) n;
        }

        Logger::OutputFunc g_output = defaultOutput;

        //
        void defaultFlush() {
            fflush(stdout);
        }

        Logger::FlushFunc g_flush = defaultFlush;
    }

    extern TimeZone g_logTimeZone;  //在LogImpl.cc中声明
}

using namespace rendu::log;

Logger::Logger(SourceFile file, int line)
        : log_impl_(INFO, 0, file, line) {
}

Logger::Logger(SourceFile file, int line, LogLevel level, const char *func)
        : log_impl_(level, 0, file, line) {
    log_impl_.stream_ << func << ": ";
}

Logger::Logger(SourceFile file, int line, LogLevel level)
        : log_impl_(level, 0, file, line) {
}

Logger::Logger(SourceFile file, int line, bool toAbort)
        : log_impl_(toAbort ? FATAL : ERROR, errno, file, line) {
}

Logger::~Logger() {
    log_impl_.finish();
    const LogStream::Buffer &buf(stream().buffer());
    g_output(buf.data(), buf.length());
    if (log_impl_.level_ == FATAL) {
        g_flush();
        abort();
    }
}

void Logger::setLogLevel(LogLevel level) {
    g_logLevel = level;
}

void Logger::setOutput(OutputFunc out) {
    g_output = out;
}

void Logger::setFlush(FlushFunc flush) {
    g_flush = flush;
}


void Logger::setTimeZone(const TimeZone &tz) {
    g_logTimeZone = tz;
}

void Logger::init() {
    //init time format default beijing time
    time::TimeZone beijing(8 * 3600, "CST");
    Logger::setTimeZone(beijing);
    //TODO:other init
}