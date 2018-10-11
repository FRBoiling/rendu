//
// Created by boil on 18-10-4.
//

#ifndef RENDU_CONDITION_H
#define RENDU_CONDITION_H

#include <rendu/common/noncopyable.h>
#include "Mutex.h"

namespace rendu {
    namespace thread {

        class Condition : rendu::noncopyable {
        public:
            explicit Condition(MutexLock &mutex)
                    : mutex_(mutex) {
                MCHECK(pthread_cond_init(&pcond_, NULL));
            }

            ~Condition() {
                MCHECK(pthread_cond_destroy(&pcond_));
            }

            void wait() {
                MutexLock::UnassignGuard ug(mutex_);
                MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
            }

            // returns true if time out, false otherwise.
            bool waitForSeconds(double seconds);

            void notify() {
                MCHECK(pthread_cond_signal(&pcond_));
            }

            void notifyAll() {
                MCHECK(pthread_cond_broadcast(&pcond_));
            }

        private:
            MutexLock &mutex_;
            pthread_cond_t pcond_;
        };

    }
}

#endif //RENDU_CONDITION_H
