//
// Created by boil on 18-10-11.
//

#include <rendu/thread/CurrentThread.h>
#include <rendu/common/Singleton.h>
#include <rendu/thread/Thread.h>

using namespace rendu;
using namespace rendu::thread;

class Test : rendu::noncopyable {
public:
    Test() {
        printf("tid=%d, constructing %p\n", CurrentThread::tid(), this);
    }

    ~Test() {
        printf("tid=%d, destructing %p %s\n", CurrentThread::tid(), this, name_.c_str());
    }

    const string &name() const { return name_; }

    void setName(const string &n) { name_ = n; }

private:
    string name_;
};

class TestNoDestroy : rendu::noncopyable {
public:
    // Tag member for Singleton<T>
    void no_destroy() {
        printf("no_destroy");
    }

    TestNoDestroy() {
        printf("tid=%d, constructing TestNoDestroy %p\n", CurrentThread::tid(), this);
    }

    ~TestNoDestroy() {
        printf("tid=%d, destructing TestNoDestroy %p\n", CurrentThread::tid(), this);
    }
};

void threadFunc() {
    printf("tid=%d, %p name=%s\n",
           CurrentThread::tid(),
           &Singleton<Test>::instance(),
           Singleton<Test>::instance().name().c_str());
    Singleton<Test>::instance().setName("only one, changed");
}

int main() {
    Singleton<Test>::instance().setName("only one");
    Thread t1(threadFunc);
    t1.start();
    t1.join();
    printf("tid=%d, %p name=%s\n",
           CurrentThread::tid(),
           &Singleton<Test>::instance(),
           Singleton<Test>::instance().name().c_str());
    Singleton<TestNoDestroy>::instance();
    printf("with valgrind, you should see %zd-byte memory leak.\n", sizeof(TestNoDestroy));
}