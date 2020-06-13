//
// Created by boil on 20-4-21.
//

#ifndef REND_TIMERID_H
#define REND_TIMERID_H

#include "Copyable.h"
#include "Types.h"

namespace rendu
{
    class Timer;

    class TimerId : public Copyable
    {
        ///
        /// An opaque identifier, for canceling Timer.
        ///
    public:
        TimerId()
            : timer_(NULL),
              sequence_(0)
        {
        }

        TimerId(Timer *timer, int64_t seq)
            : timer_(timer),
              sequence_(seq)
        {
        }

        // default copy-ctor, dtor and assignment are okay

        friend class TimerQueue;

    private:
        Timer *timer_;
        int64_t sequence_;
    };
} // namespace rendu

#endif //REND_TIMERID_H
