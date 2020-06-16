//
// Created by boil on 20-4-24.
//

#ifndef RENDU_EVENTLOOPTHREAD_H
#define RENDU_EVENTLOOPTHREAD_H

#include "EventLoop.h"

#include <rendu/common/noncopyable.h>
#include <rendu/thread/Thread.h>
#include <rendu/thread/Condition.h>

namespace rendu{
    using namespace thread;
    namespace net{
        class EventLoopThread : rendu::noncopyable
        {
        public:
            typedef boost::function<void(EventLoop*)> ThreadInitCallback;

            EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),
                            const string& name = string());
            ~EventLoopThread();
            EventLoop* startLoop();

        private:
            void threadFunc();

            EventLoop* loop_;
            bool exiting_;
            Thread thread_;
            MutexLock mutex_;
            Condition cond_;
            ThreadInitCallback callback_;
        };
    }
}


#endif //RENDU_EVENTLOOPTHREAD_H
