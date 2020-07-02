#include "../includes/Singleton.h"
#include "../includes/CurrentThread.h"
#include "../includes/Thread.h"

#include <stdio.h>

class Test : rendu::Noncopyable
{
public:
    Test()
    {
        printf("tid=%d, constructing %p\n", rendu::CurrentThread::tid(), this);
    }

    ~Test()
    {
        printf("tid=%d, destructing %p %s\n", rendu::CurrentThread::tid(), this, name_.c_str());
    }

    const rendu::string &name() const { return name_; }
    void setName(const rendu::string &n) { name_ = n; }

private:
    rendu::string name_;
};

class TestNoDestroy : rendu::Noncopyable
{
public:
    // Tag member for Singleton<T>
    void no_destroy();

    TestNoDestroy()
    {
        printf("tid=%d, constructing TestNoDestroy %p\n", rendu::CurrentThread::tid(), this);
    }

    ~TestNoDestroy()
    {
        printf("tid=%d, destructing TestNoDestroy %p\n", rendu::CurrentThread::tid(), this);
    }
};

void threadFunc()
{
    printf("tid=%d, %p name=%s\n",
           rendu::CurrentThread::tid(),
           &rendu::Singleton<Test>::instance(),
           rendu::Singleton<Test>::instance().name().c_str());
    rendu::Singleton<Test>::instance().setName("only one, changed");
}

int main()
{
    rendu::Singleton<Test>::instance().setName("only one");
    rendu::Thread t1(threadFunc);
    t1.start();
    t1.join();
    printf("tid=%d, %p name=%s\n",
           rendu::CurrentThread::tid(),
           &rendu::Singleton<Test>::instance(),
           rendu::Singleton<Test>::instance().name().c_str());
    rendu::Singleton<TestNoDestroy>::instance();
    printf("with valgrind, you should see %zd-byte memory leak.\n", sizeof(TestNoDestroy));
}