//
// Created by boil on 18-10-10.
//

#include <rendu/thread/Thread.h>
#include <rendu/thread/CurrentThread.h>
#include <rendu/thread/Mutex.h>

#include <rendu/time/Timestamp.h>
#include <map>
#include <sys/wait.h>

using namespace rendu;
using namespace rendu::time;
using namespace rendu::thread;

thread::MutexLock g_mutex;
std::map<int, int> g_delays;

void threadFunc() {
    //printf("tid=%d\n", muduo::CurrentThread::tid());
}

void threadFunc2(Timestamp start) {
    Timestamp now(Timestamp::now());
    int delay = static_cast<int>(timeDifference(now, start) * 1000000);
    MutexLockGuard lock(g_mutex);
    ++g_delays[delay];
}

void forkBench() {
//    sleep(10);
    Timestamp start(Timestamp::now());
    int kProcesses = 10 * 1000;

    for (int i = 0; i < kProcesses; ++i) {
        pid_t child = fork();
        if (child == 0) {
            exit(0);
        } else {
            waitpid(child, nullptr, 0);
        }
    }

    double timeUsed = timeDifference(Timestamp::now(), start);
    printf("process creation time used %f us\n", timeUsed * 1000000 / kProcesses);
    printf("number of created processes %d\n", kProcesses);
}

int main(int argc, char *argv[]) {
    printf("pid=%d, tid=%d\n", ::getpid(), CurrentThread::tid());
    Timestamp start(Timestamp::now());

    int kThreads = 100 * 1000;
    for (int i = 0; i < kThreads; ++i) {
        Thread t1(threadFunc);
        t1.start();
        t1.join();
    }

    double timeUsed = timeDifference(Timestamp::now(), start);
    printf("thread creation time %f us\n", timeUsed * 1000000 / kThreads);
    printf("number of created threads %d\n", Thread::numCreated());

    for (int i = 0; i < kThreads; ++i) {
        Timestamp now(Timestamp::now());
//        Thread t2(std::bind(threadFunc2, now));
        Thread t2([&]() { threadFunc2(now); });
        t2.start();
        t2.join();
    }

//    {
//        double ddd1 = 0;
//        MutexLockGuard lock(g_mutex);
//        Timestamp start1(Timestamp::now());
//        for (std::map<int, int>::iterator it = g_delays.begin();
//             it != g_delays.end(); ++it) {
//            printf("1 delay = %d, count = %d\n", it->first, it->second);
//        }
//        Timestamp end1(Timestamp::now()); 
//        ddd1 = timeDifference(end1, start1);
//        printf("1 %f\n", ddd1);
//    }

    {
        double ddd2 = 0;
        MutexLockGuard lock(g_mutex);
        Timestamp start2(Timestamp::now());
        for (auto delay:g_delays) {
            printf("2 delay = %d, count = %d\n", delay.first, delay.second);
        }
        Timestamp end2(Timestamp::now());
        ddd2 = timeDifference(end2, start2);
        printf("2 %f\n", ddd2);
    }


    forkBench();
}