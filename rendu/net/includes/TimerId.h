//
// Created by boil on 20-4-21.
//

#ifndef REND_NET_TIMERID_H
#define REND_NET_TIMERID_H

#include "rendu/base/rendu_base.h"

namespace rendu
{
    class Timer;

    namespace net
    {

        ///
        /// An opaque identifier, for canceling Timer.
        ///
        class TimerId : public Copyable
        {
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

    } // namespace net
} // namespace rendu

#endif //REND_NET_TIMERID_H
