// #include "../includes/ThreadLocal.h"
// #include "../includes/CurrentThread.h"
// #include "../includes/Thread.h"

// #include <stdio.h>

// class Test : rendu::noncopyable
// {
//  public:
//   Test()
//   {
//     printf("tid=%d, constructing %p\n", rendu::CurrentThread::tid(), this);
//   }

//   ~Test()
//   {
//     printf("tid=%d, destructing %p %s\n", rendu::CurrentThread::tid(), this, name_.c_str());
//   }

//   const rendu::string& name() const { return name_; }
//   void setName(const rendu::string& n) { name_ = n; }

//  private:
//   rendu::string name_;
// };

// rendu::ThreadLocal<Test> testObj1;
// rendu::ThreadLocal<Test> testObj2;

// void print()
// {
//   printf("tid=%d, obj1 %p name=%s\n",
//          rendu::CurrentThread::tid(),
//          &testObj1.value(),
//          testObj1.value().name().c_str());
//   printf("tid=%d, obj2 %p name=%s\n",
//          rendu::CurrentThread::tid(),
//          &testObj2.value(),
//          testObj2.value().name().c_str());
// }

// void threadFunc()
// {
//   print();
//   testObj1.value().setName("changed 1");
//   testObj2.value().setName("changed 42");
//   print();
// }

// int main()
// {
//   testObj1.value().setName("main one");
//   print();
//   rendu::Thread t1(threadFunc);
//   t1.start();
//   t1.join();
//   testObj2.value().setName("main two");
//   print();

//   pthread_exit(0);
// }
