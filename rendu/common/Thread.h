//
// Created by boil on 20-4-24.
//

#ifndef RENDU_THREAD_H
#define RENDU_THREAD_H

#include "noncopyable.h"
#include "Types.h"
#include "CountDownLatch.h"
#include "Atomic.h"

#include <boost/function.hpp>

namespace rendu {

    class Thread : noncopyable {
    public:
        typedef boost::function<void()> ThreadFunc;

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

        static int numCreated() { return numCreated_.get(); }

    private:
        void setDefaultName();

        bool started_;
        bool joined_;
        pthread_t pthreadId_;
        pid_t tid_;
        ThreadFunc func_;
        string name_;
        CountDownLatch latch_;

        static AtomicInt32 numCreated_;
    };
}

#endif //RENDU_THREAD_H
