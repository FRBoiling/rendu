//
// Created by boil on 18-10-11.
//

#include <rendu/thread/ThreadPool.h>
#include <rendu/log/Logger.h>

using namespace rendu::thread;
using namespace rendu::log;

void print()
{
    printf("tid=%d\n", CurrentThread::tid());
}

void printString(const std::string& str)
{
    LOG_INFO << str;
    usleep(100*1000);
}

void test(int maxSize)
{
    LOG_WARN << "test ThreadPool with max queue size = " << maxSize;
    ThreadPool pool("MainThreadPool");
    pool.setMaxQueueSize(maxSize);
    pool.start(5);

    LOG_WARN << "Adding";
    pool.run(print);
    pool.run(print);
    for (int i = 0; i < 100; ++i)
    {
        char buf[32];
        snprintf(buf, sizeof buf, "task %d", i);
//        pool.run(boost::bind(printString, std::string(buf)));
        pool.run([buf](){printString(std::string(buf));});
    }
    LOG_WARN << "Done";

    CountDownLatch latch(1);
    pool.run(std::bind(&CountDownLatch::countDown, &latch));
    latch.wait();
    pool.stop();
}

int main()
{
    test(0);
    test(1);
    test(5);
    test(10);
    test(50);
}