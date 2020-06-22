//
// Created by boil on 18-10-9.
//

#ifndef RENDU_ASYNCLOGGER_H
#define RENDU_ASYNCLOGGER_H

#include "StringPiece.h"
#include "Noncopyable.h"
#include "Thread.h"
#include "LogStream.h"
#include "Atomic.h"

#include <vector>

namespace rendu
{
    class AsyncLogger : Noncopyable
    {
    public:
        AsyncLogger(const string &basename,
                     off_t rollSize,
                     int flushInterval = 3);

        ~AsyncLogger()
        {
            if (running_.get())
            {
                stop();
            }
        }

        void append(const char *logline, int len);

        void start()
        {
            running_ .getAndSet(true);
            thread_.start();
            latch_.wait();
        }

        void stop() NO_THREAD_SAFETY_ANALYSIS
        {
            running_.getAndSet(false);
            cond_.notify();
            thread_.join();
        }

    private:
        void threadFunc();

        typedef FixedBuffer<rendu::kLargeBuffer> Buffer;
        typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
        typedef BufferVector::value_type BufferPtr;

        const int flushInterval_;
        AtomicBoolean running_;
        const string basename_;
        const off_t rollSize_;
        rendu::Thread thread_;
        rendu::CountDownLatch latch_;
        rendu::MutexLock mutex_;
        rendu::Condition cond_ GUARDED_BY(mutex_);
        BufferPtr currentBuffer_ GUARDED_BY(mutex_);
        BufferPtr nextBuffer_ GUARDED_BY(mutex_);
        BufferVector buffers_ GUARDED_BY(mutex_);
    };

} // namespace rendu

#endif //RENDU_ASYNCLOGGER_H
