//
// Created by boil on 20-4-24.
//

#include "Timer.h"

using namespace rendu;
using namespace rendu::net;

AtomicInt64 Timer::s_numCreated_;

void Timer::restart(Timestamp now)
{
    if (repeat_)
    {
        expiration_ = addTime(now, interval_);
    }
    else
    {
        expiration_ = Timestamp::invalid();
    }
}