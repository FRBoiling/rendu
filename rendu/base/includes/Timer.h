//
// Created by boil on 20-4-24.
//

#ifndef RENDU_TIMER_H
#define RENDU_TIMER_H

#include "Noncopyable.h"
#include "Atomic.h"
#include "Timestamp.h"
#include <functional>

namespace rendu
{
    typedef std::function<void()> TimerCallback;
    ///
    /// Internal class for timer event.
    ///
    class Timer : Noncopyable
    {
    public:
        Timer(TimerCallback cb, Timestamp when, double interval)
            : callback_(std::move(cb)),
              expiration_(when),
              interval_(interval),
              repeat_(interval > 0.0),
              sequence_(s_numCreated_.incrementAndGet())
        {
        }

        void run() const
        {
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

} // namespace rendu
#endif //RENDU_TIMER_H
