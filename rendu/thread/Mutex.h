//
// Created by boil on 18-10-4.
//

#ifndef RENDU_MUTEX_H
#define RENDU_MUTEX_H

#include <rendu/common/noncopyable.h>
#include <assert.h>
#include "CurrentThread.h"

namespace rendu {
    namespace thread {
        // Use as data member of a class, eg.
//
// class Foo
// {
//  public:
//   int size() const;
//
//  private:
//   mutable Mutex mutex_;
//   std::vector<int> data_; // GUARDED BY mutex_
// };
        class MutexLock : rendu::noncopyable {
        public:
            MutexLock()
                    : holder_(0) {
                MCHECK(pthread_mutex_init(&mutex_, NULL));
            }

            ~MutexLock() {
                assert(holder_ == 0);
                MCHECK(pthread_mutex_destroy(&mutex_));
            }

            // must be called when locked, i.e. for assertion
            bool isLockedByThisThread() const {
                return holder_ == CurrentThread::tid();
            }

            void assertLocked() const {
                assert(isLockedByThisThread());
            }

            // internal usage

            void lock() {
                MCHECK(pthread_mutex_lock(&mutex_));
                assignHolder();
            }

            void unlock() {
                unassignHolder();
                MCHECK(pthread_mutex_unlock(&mutex_));
            }

            pthread_mutex_t *getPthreadMutex() /* non-const */
            {
                return &mutex_;
            }

        private:
            friend class Condition;

            class UnassignGuard : rendu::noncopyable {
            public:
                UnassignGuard(MutexLock &owner)
                        : owner_(owner) {
                    owner_.unassignHolder();
                }

                ~UnassignGuard() {
                    owner_.assignHolder();
                }

            private:
                MutexLock &owner_;
            };

            void unassignHolder() {
                holder_ = 0;
            }

            void assignHolder() {
                holder_ = CurrentThread::tid();
            }

            pthread_mutex_t mutex_;
            pid_t holder_;
        };


// Use as a stack variable, eg.
// int Foo::size() const
// {
//   MutexLockGuard lock(mutex_);
//   return data_.size();
// }
        class MutexLockGuard : rendu::noncopyable {
        public:
            explicit MutexLockGuard(MutexLock &mutex)
                    : mutex_(mutex) {
                mutex_.lock();
            }

            ~MutexLockGuard() {
                mutex_.unlock();
            }

        private:

            MutexLock &mutex_;
        };

// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!
#define MutexLockGuard(x) error "Missing guard object name"

    }
}

#endif //RENDU_MUTEX_H
