//
// Created by boil on 18-10-4.
//

#include <atomic>
#include <rendu/log/Logger.h>
#include "Thread.h"

using namespace rendu::thread;
using namespace rendu::log;

namespace rendu {
    namespace thread {

        struct ThreadData {
            typedef Thread::ThreadFunc ThreadFunc;
            const ThreadFunc func_;
            const string name_;
            pid_t *tid_;
            CountDownLatch *latch_;

//            ThreadData(ThreadFunc func, string name, pid_t *tid, CountDownLatch *latch)
//                    : func_(move(func)),
//                      name_(move(name)),
//                      tid_(tid),
//                      latch_(latch) {}


            ThreadData(const ThreadFunc &func,const string &name, pid_t *tid, CountDownLatch *latch)
                    : func_(func),
                      name_(name),
                      tid_(tid),
                      latch_(latch) {}

            void runInThread() {
                *tid_ = CurrentThread::tid();
                tid_ = nullptr;
                latch_->countDown();
                latch_ = nullptr;

                CurrentThread::t_threadName = name_.empty() ? "muduoThread" : name_.c_str();

                prctl(PR_SET_NAME, CurrentThread::t_threadName);

                try {
                    func_();
                    CurrentThread::t_threadName = "finished";
                }
                catch (const Exception &ex) {
                    CurrentThread::t_threadName = "crashed";
                    fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
                    fprintf(stderr, "reason: %s\n", ex.what());
                    fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
                    abort();
                }
                catch (const std::exception &ex) {
                    CurrentThread::t_threadName = "crashed";
                    fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
                    fprintf(stderr, "reason: %s\n", ex.what());
                    abort();
                }
                catch (...) {
                    CurrentThread::t_threadName = "crashed";
                    fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
                    throw; // rethrow
                }
            }
        };

        std::atomic_int32_t Thread::numCreated_;
    }
}

Thread::Thread(ThreadFunc func,  string n)
        : started_(false),
          joined_(false),
          pthreadId_(0),
          tid_(0),
          func_(std::move(func)),
          name_(std::move(n)),
          latch_(1) {
    setDefaultName();
}

Thread::~Thread() {
    if (started_ && !joined_) {
        pthread_detach(pthreadId_);
    }
}

void Thread::setDefaultName() {
//    int num = numCreated_.incrementAndGet();
    int num = numCreated_++;
    if (name_.empty()) {
        char buf[32];
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
    }
}

void *startThread(void *obj) {
    auto data = static_cast<ThreadData *>(obj);
    data->runInThread();
    delete data;
    return nullptr;
}

void Thread::start() {
    assert(!started_);
    started_ = true;
    auto data = new ThreadData(func_, name_, &tid_, &latch_);
    if (pthread_create(&pthreadId_, nullptr, &startThread, data)) {
        started_ = false;
        delete data; // or no delete?
        LOG_SYSFATAL << "Failed in pthread_create";
    } else {
        latch_.wait();
        assert(tid_ > 0);
    }
}

int Thread::join() {
    assert(started_);
    assert(!joined_);
    joined_ = true;
    return pthread_join(pthreadId_, nullptr);
}