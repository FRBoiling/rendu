//
// Created by boil on 18-10-7.
//

#ifndef RENDU_THREADPOOL_H
#define RENDU_THREADPOOL_H


#include <rendu/common/noncopyable.h>
#include <rendu/common/types.h>
#include "Condition.h"
#include "Thread.h"
#include <deque>
#include <boost/ptr_container/ptr_vector.hpp>

namespace rendu {
    namespace thread {

        class ThreadPool : rendu::noncopyable {
        public:
            typedef std::function<void()> Task;

            explicit ThreadPool(const string &nameArg = string("ThreadPool"));

            ~ThreadPool();

            // Must be called before start().
            void setMaxQueueSize(int maxSize) { maxQueueSize_ = maxSize; }

            void setThreadInitCallback(const Task &cb) { threadInitCallback_ = cb; }

            void start(int numThreads);

            void stop();

            const string &name() const { return name_; }

            size_t queueSize() const;

            // Could block if maxQueueSize > 0
            void run(const Task &f);

#ifdef __GXX_EXPERIMENTAL_CXX0X__

            void run(Task &&f);

#endif

        private:
            bool isFull() const;

            void runInThread();

            Task take();

            mutable MutexLock mutex_;
            Condition notEmpty_;
            Condition notFull_;
            string name_;
            Task threadInitCallback_;
            boost::ptr_vector<Thread> threads_;
            std::deque<Task> queue_;
            size_t maxQueueSize_;
            bool running_;
        };
    }
}
#endif //RENDU_THREADPOOL_H
