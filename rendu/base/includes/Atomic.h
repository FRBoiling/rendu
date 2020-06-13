//
// Created by boil on 18-10-4.
//

#ifndef RENDU_ATOMIC_H
#define RENDU_ATOMIC_H

#include "Noncopyable.h"

#include <stdint.h>

namespace rendu
{
    template <typename T>
    class AtomicIntegerT : Noncopyable
    {
    public:
        AtomicIntegerT()
            : value_(0)
        {
        }

        // uncomment if you need copying and assignment
        //
        // AtomicIntegerT(const AtomicIntegerT& that)
        //   : value_(that.get())
        // {}
        //
        // AtomicIntegerT& operator=(const AtomicIntegerT& that)
        // {
        //   getAndSet(that.get());
        //   return *this;
        // }

        T get()
        {
            // in gcc >= 4.7: __atomic_load_n(&value_, __ATOMIC_SEQ_CST)
            return __sync_val_compare_and_swap(&value_, 0, 0);
        }

        T getAndAdd(T x)
        {
            // in gcc >= 4.7: __atomic_fetch_add(&value_, x, __ATOMIC_SEQ_CST)
            return __sync_fetch_and_add(&value_, x);
        }

        T addAndGet(T x)
        {
            return getAndAdd(x) + x;
        }

        T incrementAndGet()
        {
            return addAndGet(1);
        }

        T decrementAndGet()
        {
            return addAndGet(-1);
        }

        void add(T x)
        {
            getAndAdd(x);
        }

        void increment()
        {
            incrementAndGet();
        }

        void decrement()
        {
            decrementAndGet();
        }

        T getAndSet(T newValue)
        {
            // in gcc >= 4.7: __atomic_exchange_n(&value_, newValue, __ATOMIC_SEQ_CST)
            return __sync_lock_test_and_set(&value_, newValue);
        }

    private:
        volatile T value_;
    };

    typedef AtomicIntegerT<int32_t> AtomicInt32;
    typedef AtomicIntegerT<int64_t> AtomicInt64;

    template <typename T>
    class AtomicBooleanT : Noncopyable
    {
    public:
        AtomicBooleanT()
            : value_(false)
        {
        }

        // uncomment if you need copying and assignment
        //
        // AtomicIntegerT(const AtomicIntegerT& that)
        //   : value_(that.get())
        // {}
        //
        // AtomicIntegerT& operator=(const AtomicIntegerT& that)
        // {
        //   getAndSet(that.get());
        //   return *this;
        // }

        T get()
        {
            return __sync_bool_compare_and_swap(&value_, false, false);
        }

        T getAndSet(T newValue)
        {
            // in gcc >= 4.7: __atomic_exchange_n(&value_, newValue, __ATOMIC_SEQ_CST)
            return __sync_lock_test_and_set(&value_, newValue);
        }

    private:
        volatile T value_;
    };

} // namespace rendu
#endif // RENDU_ATOMIC_H