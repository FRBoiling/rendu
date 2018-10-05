//
// Created by boil on 18-10-4.
//

#ifndef RENDU_THREAD_H
#define RENDU_THREAD_H


#include <boost/noncopyable.hpp>
#include <functional>
#include <rendu/common/types.h>
#include <atomic>
#include "CountDownLatch.h"
#include "CurrentThread.h"

#include <sys/prctl.h>
#include <rendu/common/Exception.h>


namespace rendu {
    namespace thread {

        class Thread : boost::noncopyable {
        public:
            typedef std::function<void()> ThreadFunc;

            explicit Thread(const ThreadFunc &, const string &name = string());

#ifdef __GXX_EXPERIMENTAL_CXX0X__

            explicit Thread(ThreadFunc &&, const string &name = string());

#endif

            ~Thread();

            void start();

            int join(); // return pthread_join()

            bool started() const { return started_; }

            // pthread_t pthreadId() const { return pthreadId_; }
            pid_t tid() const { return tid_; }

            const string &name() const { return name_; }

            static int numCreated() { return numCreated_; }

        private:
            void setDefaultName();

            bool started_;
            bool joined_;
            pthread_t pthreadId_;
            pid_t tid_;
            ThreadFunc func_;
            string name_;
            CountDownLatch latch_;

            static std::atomic_int32_t numCreated_;
        };


        struct ThreadData {
            typedef Thread::ThreadFunc ThreadFunc;
            ThreadFunc func_;
            string name_;
            pid_t *tid_;
            CountDownLatch *latch_;

            ThreadData(const ThreadFunc &func,
                       const string &name,
                       pid_t *tid,
                       CountDownLatch *latch)
                    : func_(func),
                      name_(name),
                      tid_(tid),
                      latch_(latch) {}

            void runInThread() {
                *tid_ = CurrentThread::tid();
                tid_ = NULL;
                latch_->countDown();
                latch_ = NULL;

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
    }
}

#endif //RENDU_THREAD_H
