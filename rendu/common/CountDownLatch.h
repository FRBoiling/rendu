//
// Created by boil on 20-4-24.
//

#ifndef RENDU_COUNTDOWNLATCH_H
#define RENDU_COUNTDOWNLATCH_H

#include "noncopyable.h"
#include "MutexLock.h"
#include "Condition.h"

namespace rendu{
    class CountDownLatch : noncopyable
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
}


#endif //RENDU_COUNTDOWNLATCH_H
