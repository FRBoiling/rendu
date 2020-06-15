//
// Created by boil on 18-10-7.
//

#ifndef RENDU_THREADPOOL_H
#define RENDU_THREADPOOL_H

#include "Noncopyable.h"
#include "Types.h"
#include "Condition.h"
#include "Thread.h"
#include <deque>
#include <boost/ptr_container/ptr_vector.hpp>

namespace rendu
{
    class ThreadPool : Noncopyable
    {
    public:
        typedef std::function<void()> Task;

        explicit ThreadPool(const string &nameArg = string("ThreadPool"));
        ~ThreadPool();

        // Must be called before start().
        void setMaxQueueSize(int maxSize) { maxQueueSize_ = maxSize; }
        void setThreadInitCallback(const Task &cb)
        {
            threadInitCallback_ = cb;
        }

        void start(int numThreads);
        void stop();

        const string &name() const
        {
            return name_;
        }

        size_t queueSize() const;

        // Could block if maxQueueSize > 0
        // Call after stop() will return immediately.
        // There is no move-only version of std::function in C++ as of C++14.
        // So we don't need to overload a const& and an && versions
        // as we do in (Bounded)BlockingQueue.
        // https://stackoverflow.com/a/25408989
        void run(Task f);

    private:
        bool isFull() const REQUIRES(mutex_);
        void runInThread();
        Task take();

        mutable MutexLock mutex_;
        Condition notEmpty_ GUARDED_BY(mutex_);
        Condition notFull_ GUARDED_BY(mutex_);
        string name_;
        Task threadInitCallback_;
        std::vector<std::unique_ptr<rendu::Thread>> threads_;
        std::deque<Task> queue_ GUARDED_BY(mutex_);
        size_t maxQueueSize_;
        bool running_;
    };

} // namespace rendu
#endif //RENDU_THREADPOOL_H
