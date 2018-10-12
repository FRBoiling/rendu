//
// Created by boil on 18-10-10.
//

#include <rendu/thread/Thread.h>
#include <rendu/time/Timestamp.h>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

using namespace rendu;
using namespace rendu::thread;
using namespace rendu::time;

MutexLock g_mutex;
std::vector<int> g_vec;
const int kCount = 10*1000*1000;

void threadFunc()
{
    for (int i = 0; i < kCount; ++i)
    {
        thread::MutexLockGuard lock(g_mutex);
        g_vec.push_back(i);
    }
}

int foo() __attribute__ ((noinline));

int g_count = 0;
int foo()
{
    thread:: MutexLockGuard lock(g_mutex);
    if (!g_mutex.isLockedByThisThread())
    {
        printf("FAIL\n");
        return -1;
    }

    ++g_count;
    return 0;
}

int main()
{
    MCHECK(foo());
    if (g_count != 1)
    {
        printf("MCHECK calls twice.\n");
        abort();
    }

    const int kMaxThreads = 8;
    g_vec.reserve(kMaxThreads * kCount);

    Timestamp start(Timestamp::now());
    for (int i = 0; i < kCount; ++i)
    {
        g_vec.push_back(i);
    }

    printf("single thread without lock %f\n", timeDifference(Timestamp::now(), start));

    start = Timestamp::now();
    threadFunc();
    printf("single thread with lock %f\n", timeDifference(Timestamp::now(), start));

    for (int nthreads = 1; nthreads < kMaxThreads; ++nthreads)
    {
        boost::ptr_vector<Thread> threads;
        g_vec.clear();
        start = Timestamp::now();
        for (int i = 0; i < nthreads; ++i)
        {
            threads.push_back(new Thread(threadFunc));
            threads.back().start();
        }
        for (int i = 0; i < nthreads; ++i)
        {
            threads[i].join();
        }
        printf("%d thread(s) with lock %f\n", nthreads, timeDifference(Timestamp::now(), start));
    }
}
