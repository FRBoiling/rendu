//
// Created by boil on 18-10-3.
//

#ifndef RENDU_LOG_LOGSTREAM_H
#define RENDU_LOG_LOGSTREAM_H

#include <boost/noncopyable.hpp>
#include <rendu/common/StringPiece.h>
#include <rendu/common/FixedBuffer.h>
#include "LogStreamObject.h"

namespace rendu {
    namespace log {

        class LogStream : boost::noncopyable {
            typedef LogStream self;
        public:
            typedef FixedBuffer<kSmallBuffer> Buffer;

            self &operator<<(bool v) {
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

            self &operator<<(float v) {
                *this << static_cast<double>(v);
                return *this;
            }

            self &operator<<(double);
            // self& operator<<(long double);

            self &operator<<(char v) {
                buffer_.append(&v, 1);
                return *this;
            }

            // self& operator<<(signed char);
            // self& operator<<(unsigned char);

            self &operator<<(const char *str) {
                if (str) {
                    buffer_.append(str, strlen(str));
                } else {
                    buffer_.append("(null)", 6);
                }
                return *this;
            }

            self &operator<<(const unsigned char *str) {
                return operator<<(reinterpret_cast<const char *>(str));
            }

            self &operator<<(const string &v) {
                buffer_.append(v.c_str(), v.size());
                return *this;
            }

            self &operator<<(const StringPiece &v) {
                buffer_.append(v.data(), v.size());
                return *this;
            }

            self &operator<<(const Buffer &v) {
                *this << v.toStringPiece();
                return *this;
            }


            void append(const char *data, int len) { buffer_.append(data, len); }

            const Buffer &buffer() const { return buffer_; }

            void resetBuffer() { buffer_.reset(); }

        private:
            void staticCheck();

            template<typename T>
            void formatInteger(T);

            Buffer buffer_;

            static const int kMaxNumericSize = 32;
        };

        inline LogStream &operator<<(LogStream &s, T v) {
            s.append(v.str_, v.len_);
            return s;
        }

        inline LogStream &operator<<(LogStream &s, const SourceFile &sourceFile) {
            s.append(sourceFile.data_, sourceFile.size_);
            return s;
        }

        inline LogStream &operator<<(LogStream &s, const Fmt &fmt) {
            s.append(fmt.data(), fmt.length());
            return s;
        }
    }
}

#endif //RENDU_LOG_LOGSTREAM_H
