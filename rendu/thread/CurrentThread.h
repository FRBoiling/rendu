//
// Created by boil on 18-10-3.
//

#ifndef RENDU_CURRENTTHREAD_H
#define RENDU_CURRENTTHREAD_H

#include <stdint.h>
#include <pthread.h>

namespace rendu {
    namespace thread {

#ifdef CHECK_PTHREAD_RETURN_VALUE

        #ifdef NDEBUG
    __BEGIN_DECLS
    extern void __assert_perror_fail (int errnum,
                                      const char *file,
                                      unsigned int line,
                                      const char *function)
        __THROW __attribute__ ((__noreturn__));
    __END_DECLS
#endif

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       if (__builtin_expect(errnum != 0, 0))    \
                         __assert_perror_fail (errnum, __FILE__, __LINE__, __func__);})

#else  // CHECK_PTHREAD_RETURN_VALUE

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       assert(errnum == 0); (void) errnum;})

#endif // CHECK_PTHREAD_RETURN_VALUE

        namespace CurrentThread {
            // internal
            extern __thread int t_cachedTid;
            extern __thread char t_tidString[32];
            extern __thread int t_tidStringLength;
            extern __thread const char *t_threadName;

            void cacheTid();

            inline int tid() {
                if (__builtin_expect(t_cachedTid == 0, 0)) {
                    cacheTid();
                }
                return t_cachedTid;
            }

            inline const char *tidString() // for logging
            {
                return t_tidString;
            }

            inline int tidStringLength() // for logging
            {
                return t_tidStringLength;
            }

            inline const char *name() {
                return t_threadName;
            }

            bool isMainThread();

            void sleepUsec(int64_t usec);
        }
    }
}
#endif //RENDU_CURRENTTHREAD_H
