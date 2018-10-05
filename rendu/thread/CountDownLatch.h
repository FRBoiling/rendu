//
// Created by boil on 18-10-4.
//

#ifndef RENDU_COUNTDOWNLATCH_H
#define RENDU_COUNTDOWNLATCH_H


#include <boost/noncopyable.hpp>
#include "Mutex.h"
#include "Condition.h"

namespace rendu {
    namespace thread {

        class CountDownLatch : boost::noncopyable {
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
}
#endif //RENDU_COUNTDOWNLATCH_H