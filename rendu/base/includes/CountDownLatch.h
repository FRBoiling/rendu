//
// Created by boil on 18-10-4.
//

#ifndef RENDU_COUNTDOWNLATCH_H
#define RENDU_COUNTDOWNLATCH_H

#include "Noncopyable.h"
#include "Mutex.h"
#include "Condition.h"

namespace rendu
{
    class CountDownLatch : Noncopyable
    {
    public:
        explicit CountDownLatch(int count);

        void wait();

        void countDown();

        int getCount() const;

    private:
        mutable MutexLock mutex_;
        Condition condition_;
        int count_;
    };

} // namespace rendu
#endif //RENDU_COUNTDOWNLATCH_H
