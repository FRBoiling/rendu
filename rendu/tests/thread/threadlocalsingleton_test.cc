//
// Created by boil on 18-10-11.
//

#include <rendu/thread/CurrentThread.h>
#include <rendu/thread/ThreadLocalSingleton.h>
#include <rendu/thread/Thread.h>

using namespace rendu;
using namespace rendu::thread;

class Test
{
public:
    Test()
    {
        printf("tid=%d, constructing %p\n", CurrentThread::tid(), this);
    }

    ~Test()
    {
        printf("tid=%d, destructing %p %s\n", CurrentThread::tid(), this, name_.c_str());
    }

    const string& name() const { return name_; }
    void setName(const string& n) { name_ = n; }

private:
    string name_;
};

void threadFunc(const char* changeTo)
{
    printf("tid=%d, %p name=%s\n",
           CurrentThread::tid(),
           &ThreadLocalSingleton<Test>::instance(),
           ThreadLocalSingleton<Test>::instance().name().c_str());
    ThreadLocalSingleton<Test>::instance().setName(changeTo);
    printf("tid=%d, %p name=%s\n",
           CurrentThread::tid(),
           &ThreadLocalSingleton<Test>::instance(),
           ThreadLocalSingleton<Test>::instance().name().c_str());

    // no need to manually delete it
    // muduo::ThreadLocalSingleton<Test>::destroy();
}

int main()
{
    ThreadLocalSingleton<Test>::instance().setName("main one");
//    Thread t1(boost::bind(threadFunc, "thread1"));
//    Thread t2(boost::bind(threadFunc, "thread2"));
    Thread t1([](){threadFunc("thread1");});
    Thread t2([](){threadFunc("thread2");});
    t1.start();
    t2.start();
    t1.join();
    printf("tid=%d, %p name=%s\n",
           CurrentThread::tid(),
           &ThreadLocalSingleton<Test>::instance(),
           ThreadLocalSingleton<Test>::instance().name().c_str());
    t2.join();

    pthread_exit(nullptr);
}