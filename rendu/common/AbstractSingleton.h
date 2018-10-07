//
// Created by boil on 18-10-7.
//

#ifndef RENDU_ABSTRACTSINGLETON_H
#define RENDU_ABSTRACTSINGLETON_H

#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace rendu {

// This doesn't detect inherited member functions!
// http://stackoverflow.com/questions/1966362/sfinae-to-check-for-inherited-member-functions
    template<typename T>
    struct has_no_destroy {
#ifdef __GXX_EXPERIMENTAL_CXX0X__

        template<typename C>
        static char test(decltype(&C::no_destroy));

#else
        template <typename C> static char test(typeof(&C::no_destroy));
#endif

        template<typename C>
        static int32_t test(...);

        const static bool value = sizeof(test<T>(0)) == 1;
    };

    template<typename T>
    class Singleton : boost::noncopyable {
    public:
        static T &instance() {
            pthread_once(&ponce_, &Singleton::init);
            assert(value_ != NULL);
            return *value_;
        }

    private:
        Singleton();

        ~Singleton();

        static void init() {
            value_ = new T();
            if (!has_no_destroy<T>::value) {
                ::atexit(destroy);
            }
        }

        static void destroy() {
            typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
            T_must_be_complete_type dummy;
            (void) dummy;

            delete value_;
            value_ = NULL;
        }

    private:
        static pthread_once_t ponce_;
        static T *value_;
    };

    template<typename T>
    pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

    template<typename T>
    T* Singleton<T>::value_ = NULL;

}

#endif //RENDU_ABSTRACTSINGLETON_H