//
// Created by boil on 18-10-4.
//

#include <atomic>
#include <rendu/log/Logger.h>
#include "Thread.h"

using namespace rendu::thread;
using namespace rendu::log;

std::atomic_int32_t Thread::numCreated_;

Thread::Thread(const ThreadFunc& func, const string& n)
        : started_(false),
          joined_(false),
          pthreadId_(0),
          tid_(0),
          func_(func),
          name_(n),
          latch_(1)
{
    setDefaultName();
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
Thread::Thread(ThreadFunc&& func, const string& n)
        : started_(false),
          joined_(false),
          pthreadId_(0),
          tid_(0),
          func_(std::move(func)),
          name_(n),
          latch_(1)
{
    setDefaultName();
}

#endif

Thread::~Thread()
{
    if (started_ && !joined_)
    {
        pthread_detach(pthreadId_);
    }
}

void Thread::setDefaultName()
{
//    int num = numCreated_.incrementAndGet();
    int num = numCreated_++;
    if (name_.empty())
    {
        char buf[32];
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
    }
}

void *startThread(void *obj) {
    ThreadData *data = static_cast<ThreadData *>(obj);
    data->runInThread();
    delete data;
    return NULL;
}

void Thread::start()
{
    assert(!started_);
    started_ = true;
    // FIXME: move(func_)
    ThreadData* data = new ThreadData(func_, name_, &tid_, &latch_);
    if (pthread_create(&pthreadId_, NULL, &startThread, data))
    {
        started_ = false;
        delete data; // or no delete?
        LOG_SYSFATAL << "Failed in pthread_create";
    }
    else
    {
        latch_.wait();
        assert(tid_ > 0);
    }
}

int Thread::join()
{
    assert(started_);
    assert(!joined_);
    joined_ = true;
    return pthread_join(pthreadId_, NULL);
}