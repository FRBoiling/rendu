//
// Created by boil on 20-4-24.
//

#ifndef RENDU_TIMER_H
#define RENDU_TIMER_H


#include <rendu/time/Timestamp.h>
#include <rendu/common/noncopyable.h>
#include <rendu/common/Atomic.h>
#include "Callbacks.h"

namespace rendu {
    namespace net {
///
/// Internal class for timer event.
///
        class Timer : rendu::noncopyable {
        public:
            Timer(const TimerCallback &cb, Timestamp when, double interval)
                    : callback_(cb),
                      expiration_(when),
                      interval_(interval),
                      repeat_(interval > 0.0),
                      sequence_(s_numCreated_.incrementAndGet()) {}

#ifdef __GXX_EXPERIMENTAL_CXX0X__

            Timer(TimerCallback &&cb, Timestamp when, double interval)
                    : callback_(std::move(cb)),
                      expiration_(when),
                      interval_(interval),
                      repeat_(interval > 0.0),
                      sequence_(s_numCreated_.incrementAndGet()) {}

#endif

            void run() const {
                callback_();
            }

            Timestamp expiration() const { return expiration_; }

            bool repeat() const { return repeat_; }

            int64_t sequence() const { return sequence_; }

            void restart(Timestamp now);

            static int64_t numCreated() { return s_numCreated_.get(); }

        private:
            const TimerCallback callback_;
            Timestamp expiration_;
            const double interval_;
            const bool repeat_;
            const int64_t sequence_;

            static AtomicInt64 s_numCreated_;
        };
    }
}


#endif //RENDU_TIMER_H
