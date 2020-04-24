//
// Created by boil on 20-4-21.
//

#ifndef RENDU_TIMERID_H
#define RENDU_TIMERID_H

#include <rendu/common/copyable.h>
#include <rendu/common/Types.h>
#include "Timer.h"

namespace rendu
{
    namespace net{
///
/// An opaque identifier, for canceling Timer.
///
        class TimerId:public rendu::copyable {
        public:
            TimerId()
                    : timer_(NULL),
                      sequence_(0)
            {
            }

            TimerId(Timer* timer, int64_t seq)
            : timer_(timer),
            sequence_(seq)
            {
            }

            // default copy-ctor, dtor and assignment are okay

            friend class TimerQueue;

        private:
            Timer* timer_;
            int64_t sequence_;
        };
    }
}


#endif //RENDU_TIMERID_H
