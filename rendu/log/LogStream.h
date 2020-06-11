//
// Created by boil on 18-10-3.
//

#ifndef RENDU_LOG_LOGSTREAM_H
#define RENDU_LOG_LOGSTREAM_H

#include "rendu/common/noncopyable.h"
#include "rendu/common/stringpiece.h"
#include "rendu/detail/FixedBuffer.h"

namespace rendu
{
    namespace log
    {

        class LogStream : noncopyable
        {
            typedef LogStream self;

        public:
            typedef detail::FixedBuffer<detail::kSmallBuffer> Buffer;

            self &operator<<(bool v)
            {
                buffer_.append(v ? "1" : "0", 1);
                return *this;
            }

            self &operator<<(short);
            self &operator<<(unsigned short);
            self &operator<<(int);
            self &operator<<(unsigned int);
            self &operator<<(long);
            self &operator<<(unsigned long);
            self &operator<<(long long);
            self &operator<<(unsigned long long);

            self &operator<<(const void *);

            self &operator<<(float v)
            {
                *this << static_cast<double>(v);
                return *this;
            }
            self &operator<<(double);
            // self& operator<<(long double);

            self &operator<<(char v)
            {
                buffer_.append(&v, 1);
                return *this;
            }

            // self& operator<<(signed char);
            // self& operator<<(unsigned char);

            self &operator<<(const char *str)
            {
                if (str)
                {
                    buffer_.append(str, strlen(str));
                }
                else
                {
                    buffer_.append("(null)", 6);
                }
                return *this;
            }

            self &operator<<(const unsigned char *str)
            {
                return operator<<(reinterpret_cast<const char *>(str));
            }

            self &operator<<(const string &v)
            {
                buffer_.append(v.c_str(), v.size());
                return *this;
            }

            self &operator<<(const StringPiece &v)
            {
                buffer_.append(v.data(), v.size());
                return *this;
            }

            self &operator<<(const Buffer &v)
            {
                *this << v.toStringPiece();
                return *this;
            }

            void append(const char *data, int len) { buffer_.append(data, len); }
            const Buffer &buffer() const { return buffer_; }
            void resetBuffer() { buffer_.reset(); }

        private:
            void staticCheck();

            template <typename T>
            void formatInteger(T);

            Buffer buffer_;

            static const int kMaxNumericSize = 32;
        };


        class Fmt // : noncopyable
        {
        public:
            template <typename T>
            Fmt(const char *fmt, T val);

            const char *data() const { return buf_; }
            int length() const { return length_; }

        private:
            char buf_[32];
            int length_;
        };

        inline LogStream &operator<<(LogStream &s, const Fmt &fmt)
        {
            s.append(fmt.data(), fmt.length());
            return s;
        }

        // Format quantity n in SI units (k, M, G, T, P, E).
        // The returned string is atmost 5 characters long.
        // Requires n >= 0
        string formatSI(int64_t n);

        // Format quantity n in IEC (binary) units (Ki, Mi, Gi, Ti, Pi, Ei).
        // The returned string is atmost 6 characters long.
        // Requires n >= 0
        string formatIEC(int64_t n);

    } // namespace log
} // namespace rendu

#endif //RENDU_LOG_LOGSTREAM_H
