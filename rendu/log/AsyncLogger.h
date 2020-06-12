//
// Created by boil on 18-10-9.
//

#ifndef RENDU_LOG_ASYNCLOGGER_H
#define RENDU_LOG_ASYNCLOGGER_H

#include <boost/ptr_container/ptr_vector.hpp>
#include <rendu/thread/Thread.h>

namespace rendu
{
    namespace log
    {

        class AsyncLogger : rendu::noncopyable
        {
        public:
            AsyncLogger(const string &basename,
                        off_t rollSize,
                        int flushInterval = 3);

            ~AsyncLogger()
            {
                if (running_)
                {
                    stop();
                }
            }

            void append(const char *logline, int len);

            void start()
            {
                running_ = true;
                thread_.start();
                latch_.wait();
            }

            void stop()
            {
                running_ = false;
                cond_.notify();
                thread_.join();
            }

        private:
            // declare but not define, prevent compiler-synthesized functions
            AsyncLogger(const AsyncLogger &);    // ptr_container
            void operator=(const AsyncLogger &); // ptr_container

            void threadFunc();

            typedef FixedBuffer<kLargeBuffer> Buffer;
            typedef boost::ptr_vector<Buffer> BufferVector;
            typedef BufferVector::auto_type BufferPtr;

            const int flushInterval_;
            bool running_;
            string basename_;
            off_t rollSize_;
            thread::Thread thread_;
            thread::CountDownLatch latch_;
            thread::MutexLock mutex_;
            thread::Condition cond_;
            BufferPtr currentBuffer_;
            BufferPtr nextBuffer_;
            BufferVector buffers_;
        };

    } // namespace log
} // namespace rendu

#endif //RENDU_ASYNCLOGGER_H
