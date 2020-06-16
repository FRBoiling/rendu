//
// Created by boil on 20-4-24.
//

#ifndef RENDU_NET_EVENTLOOPTHREAD_H
#define RENDU_NET_EVENTLOOPTHREAD_H

#include "rendu/base/rendu_base.h"
#include <functional>

namespace rendu
{
    namespace net
    {
        class EventLoop;
        class EventLoopThread : Noncopyable
        {
        public:
            typedef std::function<void(EventLoop *)> ThreadInitCallback;

            EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback(),
                            const string &name = string());
            ~EventLoopThread();
            EventLoop *startLoop();

        private:
            void threadFunc();

            EventLoop *loop_ GUARDED_BY(mutex_);
            bool exiting_;
            Thread thread_;
            MutexLock mutex_;
            Condition cond_ GUARDED_BY(mutex_);
            ThreadInitCallback callback_;
        };
    } // namespace net
} // namespace rendu

#endif //RENDU_NET_EVENTLOOPTHREAD_H
