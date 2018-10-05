//
// Created by boil on 18-10-3.
//

#ifndef RENDU_FIXEDBUFFER_H
#define RENDU_FIXEDBUFFER_H

#include "StringPiece.h"
#include <boost/noncopyable.hpp>

namespace rendu {

    const int kSmallBuffer = 4000;
    const int kLargeBuffer = 4000 * 1000;

    template<int SIZE>
    class FixedBuffer : boost::noncopyable {
    public:
        FixedBuffer()
                : cur_(data_) {
            setCookie(cookieStart);
        }

        ~FixedBuffer() {
            setCookie(cookieEnd);
        }

        void append(const char * /*restrict*/ buf, size_t len) {
            // FIXME: append partially
            if (implicit_cast<size_t>(avail()) > len) {
                memcpy(cur_, buf, len);
                cur_ += len;
            }
        }

        const char *data() const { return data_; }

        int length() const { return static_cast<int>(cur_ - data_); }

        // write to data_ directly
        char *current() { return cur_; }

        int avail() const { return static_cast<int>(end() - cur_); }

        void add(size_t len) { cur_ += len; }

        void reset() { cur_ = data_; }

        void bzero() { ::bzero(data_, sizeof data_); }

        // for used by GDB
        const char *debugString();

        void setCookie(void (*cookie)()) { cookie_ = cookie; }

        // for used by unit test
        string toString() const { return string(data_, length()); }

        StringPiece toStringPiece() const { return StringPiece(data_, length()); }

    private:
        const char *end() const { return data_ + sizeof data_; }

        // Must be outline function for cookies.
        static void cookieStart();

        static void cookieEnd();

        void (*cookie_)();

        char data_[SIZE];
        char *cur_;
    };

    template
    class FixedBuffer<kSmallBuffer>;

    template
    class FixedBuffer<kLargeBuffer>;

}

#endif //RENDU_FIXEDBUFFER_H