//
// Created by boil on 18-10-4.
//

#ifndef RENDU_THREAD_H
#define RENDU_THREAD_H

#include "rendu/common/noncopyable.h"
#include "rendu/common/types.h"
#include "CountDownLatch.h"

#include <functional>
#include <memory>
#include <pthread.h>


namespace rendu
{

    namespace thread
    {

        class Thread : rendu::noncopyable
        {
        public:
            typedef std::function<void()> ThreadFunc;

            explicit Thread(ThreadFunc threadFunc, string name = string());

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

    } // namespace thread
} // namespace rendu

#endif //RENDU_THREAD_H
