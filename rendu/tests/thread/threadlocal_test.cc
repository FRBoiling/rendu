//
// Created by boil on 18-10-11.
//

#include <rendu/thread/CurrentThread.h>
#include <rendu/log/Logger.h>
#include <rendu/thread/ThreadLocal.h>
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

ThreadLocal<Test> testObj1;
ThreadLocal<Test> testObj2;

void print()
{
    printf("tid=%d, obj1 %p name=%s\n",
           CurrentThread::tid(),
           &testObj1.value(),
           testObj1.value().name().c_str());
    printf("tid=%d, obj2 %p name=%s\n",
           CurrentThread::tid(),
           &testObj2.value(),
           testObj2.value().name().c_str());
}

void threadFunc()
{
    print();
    testObj1.value().setName("changed 1");
    testObj2.value().setName("changed 42");
    print();
}

int main()
{
    testObj1.value().setName("main one");
    print();
    Thread t1(threadFunc);
    t1.start();
    t1.join();
    testObj2.value().setName("main two");
    print();

    pthread_exit(nullptr);
}