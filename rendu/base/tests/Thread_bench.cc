#include "../includes/CurrentThread.h"
#include "../includes/Mutex.h"
#include "../includes/Thread.h"
#include "../includes/Timestamp.h"

#include <map>
#include <string>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

rendu::MutexLock g_mutex;
std::map<int, int> g_delays;

void threadFunc()
{
    //printf("tid=%d\n", rendu::CurrentThread::tid());
}

void threadFunc2(rendu::Timestamp start)
{
    rendu::Timestamp now(rendu::Timestamp::now());
    int delay = static_cast<int>(timeDifference(now, start) * 1000000);
    rendu::MutexLockGuard lock(g_mutex);
    ++g_delays[delay];
}

void forkBench()
{
    sleep(10);
    rendu::Timestamp start(rendu::Timestamp::now());
    int kProcesses = 10 * 1000;

    for (int i = 0; i < kProcesses; ++i)
    {
        pid_t child = fork();
        if (child == 0)
        {
            exit(0);
        }
        else
        {
            waitpid(child, NULL, 0);
        }
    }

    double timeUsed = timeDifference(rendu::Timestamp::now(), start);
    printf("process creation time used %f us\n", timeUsed * 1000000 / kProcesses);
    printf("number of created processes %d\n", kProcesses);
}

int main(int argc, char *argv[])
{
    printf("pid=%d, tid=%d\n", ::getpid(), rendu::CurrentThread::tid());
    rendu::Timestamp start(rendu::Timestamp::now());

    int kThreads = 100 * 1000;
    for (int i = 0; i < kThreads; ++i)
    {
        rendu::Thread t1(threadFunc);
        t1.start();
        t1.join();
    }

    double timeUsed = timeDifference(rendu::Timestamp::now(), start);
    printf("thread creation time %f us\n", timeUsed * 1000000 / kThreads);
    printf("number of created threads %d\n", rendu::Thread::numCreated());

    for (int i = 0; i < kThreads; ++i)
    {
        rendu::Timestamp now(rendu::Timestamp::now());
        rendu::Thread t2(std::bind(threadFunc2, now));
        t2.start();
        t2.join();
    }
    {
        rendu::MutexLockGuard lock(g_mutex);
        for (const auto &delay : g_delays)
        {
            printf("delay = %d, count = %d\n",
                   delay.first, delay.second);
        }
    }

    forkBench();
}
