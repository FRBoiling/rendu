//
// Created by boil on 18-10-4.
//

#include "CurrentThread.h"
#include <rendu/common/Types.h>
#include <rendu/time/Timestamp.h>
#include <sys/syscall.h>

using namespace rendu::thread;

namespace rendu{
    namespace thread{
        namespace CurrentThread {
            __thread int t_cachedTid = 0;
            __thread char t_tidString[32];
            __thread int t_tidStringLength = 6;
            __thread const char *t_threadName = "unknown";
            const bool sameType = std::is_same<int, pid_t>::value;
            static_assert(sameType,"int and pid_t is not sameType");
        }
    }
}

pid_t getTid()
{
    return static_cast<pid_t>(::syscall(SYS_gettid));
}

void CurrentThread::cacheTid()
{
    if (t_cachedTid == 0)
    {
        t_cachedTid = getTid();
        t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
    }
}

bool CurrentThread::isMainThread()
{
    return tid() == ::getpid();
}

void CurrentThread::sleepUsec(int64_t usec)
{
    struct timespec ts = { 0, 0 };
    ts.tv_sec = static_cast<time_t>(usec /time::Timestamp::kMicroSecondsPerSecond);
    ts.tv_nsec = static_cast<long>(usec % time::Timestamp::kMicroSecondsPerSecond * 1000);
    ::nanosleep(&ts, nullptr);
}
