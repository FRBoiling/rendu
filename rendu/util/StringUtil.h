//
// Created by boil on 18-10-3.
//

#ifndef RENDU_STRINGUTIL_H
#define RENDU_STRINGUTIL_H

#include <algorithm>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

namespace rendu{
    namespace util{

        // Efficient Integer to String Conversions, by Matthew Wilson.
        const char digits[] = "9876543210123456789";
        const char *zero = digits + 9;
        static_assert(sizeof(digits) == 20);

        const char digitsHex[] = "0123456789ABCDEF";
        static_assert(sizeof digitsHex == 17);

        template<typename T>
        static size_t convert(char buf[], T value) {
            T i = value;
            char *p = buf;

            do {
                int lsd = static_cast<int>(i % 10);
                i /= 10;
                *p++ = zero[lsd];
            } while (i != 0);

            if (value < 0) {
                *p++ = '-';
            }
            *p = '\0';
            std::reverse(buf, p);

            return p - buf;
        }

        static size_t convertHex(char buf[], uintptr_t value) {
            uintptr_t i = value;
            char *p = buf;

            do {
                int lsd = static_cast<int>(i % 16);
                i /= 16;
                *p++ = digitsHex[lsd];
            } while (i != 0);

            *p = '\0';
            std::reverse(buf, p);

            return p - buf;
        }

    }
}

#endif //RENDU_STRINGUTIL_H
