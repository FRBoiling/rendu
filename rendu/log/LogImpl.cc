//
// Created by boil on 18-10-3.
//

#include <rendu/thread/CurrentThread.h>
#include "LogImpl.h"
#include <rendu/time/TimeZone.h>

using namespace rendu::log;
using namespace rendu::thread;

__thread char t_errnobuf[512];

const char *strerror_tl(int savedErrno) {
    return strerror_r(savedErrno, t_errnobuf, sizeof t_errnobuf);
}

LogImpl::LogImpl(LogLevel level, int savedErrno, const SourceFile &file, int line)
        : time_(Timestamp::now()),
          stream_(),
          level_(level),
          line_(line),
          basename_(file) {
    formatTime();
    CurrentThread::tid();
    stream_ << "[" << T(CurrentThread::tidString(), CurrentThread::tidStringLength()) << "] ";
    stream_ << T(LogLevelName[level], 5);
    if (savedErrno != 0) {
        stream_ << strerror_tl(savedErrno) << " (errno=" << savedErrno << ") ";
    }
    stream_ << " - ";
}

namespace rendu {
    __thread char t_time[64];
    __thread time_t t_lastSecond;
    TimeZone g_logTimeZone;
}

void LogImpl::formatTime() {
    int64_t microSecondsSinceEpoch = time_.microSecondsSinceEpoch();
    time_t seconds = static_cast<time_t>(microSecondsSinceEpoch / Timestamp::kMicroSecondsPerSecond);
    int microseconds = static_cast<int>(microSecondsSinceEpoch % Timestamp::kMicroSecondsPerSecond);
    if (seconds != t_lastSecond) {
        t_lastSecond = seconds;
        struct tm tm_time;
        if (g_logTimeZone.valid()) {
            tm_time = g_logTimeZone.toLocalTime(seconds);
        } else {
            ::gmtime_r(&seconds, &tm_time); // FIXME TimeZone::fromUtcTime
        }

        int len = snprintf(t_time, sizeof(t_time), "%4d%02d%02d %02d:%02d:%02d",
                           tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                           tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
        assert(len == 17);
        (void) len;
    }

    if (g_logTimeZone.valid()) {
        Fmt us(".%06d ", microseconds);
        assert(us.length() == 8);
        stream_ << T(t_time, 17) << T(us.data(), 8);
    } else {
        Fmt us(".%06dZ ", microseconds);
        assert(us.length() == 9);
        stream_ << T(t_time, 17) << T(us.data(), 9);
    }
}

void LogImpl::finish() {
    stream_ << " - " << basename_ << ':' << line_ << '\n';
}