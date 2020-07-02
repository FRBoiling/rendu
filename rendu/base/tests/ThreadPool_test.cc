#include "../includes/ThreadPool.h"
#include "../includes/CountDownLatch.h"
#include "../includes/CurrentThread.h"
#include "../includes/Logger.h"

#include <stdio.h>
#include <unistd.h> // usleep

void print()
{
    printf("tid=%d\n", rendu::CurrentThread::tid());
}

void printString(const std::string &str)
{
    LOG_INFO << str;
    usleep(100 * 1000);
}

void test(int maxSize)
{
    LOG_WARN << "Test ThreadPool with max queue size = " << maxSize;
    rendu::ThreadPool pool("MainThreadPool");
    pool.setMaxQueueSize(maxSize);
    pool.start(5);

    LOG_WARN << "Adding";
    pool.run(print);
    pool.run(print);
    for (int i = 0; i < 100; ++i)
    {
        char buf[32];
        snprintf(buf, sizeof buf, "task %d", i);
        pool.run(std::bind(printString, std::string(buf)));
    }
    LOG_WARN << "Done";

    rendu::CountDownLatch latch(1);
    pool.run(std::bind(&rendu::CountDownLatch::countDown, &latch));
    latch.wait();
    pool.stop();
}

/*
 * Wish we could do this in the future.
void testMove()
{
  rendu::ThreadPool pool;
  pool.start(2);

  std::unique_ptr<int> x(new int(42));
  pool.run([y = std::move(x)]{ printf("%d: %d\n", rendu::CurrentThread::tid(), *y); });
  pool.stop();
}
*/

void longTask(int num)
{
    LOG_INFO << "longTask " << num;
    rendu::CurrentThread::sleepUsec(3000000);
}

void test2()
{
    LOG_WARN << "Test ThreadPool by stoping early.";
    rendu::ThreadPool pool("ThreadPool");
    pool.setMaxQueueSize(5);
    pool.start(3);

    rendu::Thread thread1([&pool]() {
        for (int i = 0; i < 20; ++i)
        {
            pool.run(std::bind(longTask, i));
        }
    },
                          "thread1");
    thread1.start();

    rendu::CurrentThread::sleepUsec(5000000);
    LOG_WARN << "stop pool";
    pool.stop(); // early stop

    thread1.join();
    // run() after stop()
    pool.run(print);
    LOG_WARN << "test2 Done";
}

int main()
{
    test(0);
    test(1);
    test(5);
    test(10);
    test(50);
    test2();
}
