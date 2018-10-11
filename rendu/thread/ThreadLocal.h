//
// Created by boil on 18-10-11.
//

#ifndef RENDU_THREADLOCAL_H
#define RENDU_THREADLOCAL_H

#include <rendu/common/noncopyable.h>
#include "CurrentThread.h"

namespace rendu{
    namespace thread{

        template<typename T>
        class ThreadLocal : rendu::noncopyable
        {
        public:
            ThreadLocal()
            {
                MCHECK(pthread_key_create(&pkey_, &ThreadLocal::destructor));
            }

            ~ThreadLocal()
            {
                MCHECK(pthread_key_delete(pkey_));
            }

            T& value()
            {
                T* perThreadValue = static_cast<T*>(pthread_getspecific(pkey_));
                if (!perThreadValue)
                {
                    T* newObj = new T();
                    MCHECK(pthread_setspecific(pkey_, newObj));
                    perThreadValue = newObj;
                }
                return *perThreadValue;
            }

        private:

            static void destructor(void *x)
            {
                T* obj = static_cast<T*>(x);
                typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
                T_must_be_complete_type dummy; (void) dummy;
                delete obj;
            }

        private:
            pthread_key_t pkey_;
        };

    }
}


#endif //RENDU_THREADLOCAL_H
