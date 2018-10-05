//
// Created by boil on 18-10-3.
//

#ifndef RENDU_LOGMODEL_H
#define RENDU_LOGMODEL_H

#include <rendu/common/StringPiece.h>

namespace rendu {
    namespace log {

        // helper class for known string length at compile time
        class T {
        public:
            T(const char *str, unsigned len)
                    : str_(str),
                      len_(len) {
//                int nlen = strlen(str);
                assert(strlen(str) == len_);
            }

            const char *str_;
            const unsigned len_;
        };

        //
        class SourceFile {
        public:
            template<int N>
            inline SourceFile(const char (&arr)[N])
                    : data_(arr),
                      size_(N - 1) {
                const char *slash = strrchr(data_, '/'); // builtin function
                if (slash) {
                    data_ = slash + 1;
                    size_ -= static_cast<int>(data_ - arr);
                }
            }

            explicit SourceFile(const char *filename)
                    : data_(filename) {
                const char *slash = strrchr(filename, '/');
                if (slash) {
                    data_ = slash + 1;
                }
                size_ = static_cast<int>(strlen(data_));
            }

            const char *data_;
            int size_;
        };

        //fmt
        class Fmt // : boost::noncopyable
        {
        public:
            template<typename T>
            Fmt(const char *fmt, T val);

            const char *data() const { return buf_; }

            int length() const { return length_; }

        private:
            char buf_[32];
            int length_;
        };

        template<typename T>
        Fmt::Fmt(const char *fmt, T val) {
            static_assert(std::is_arithmetic<T>::value == true);

            length_ = snprintf(buf_, sizeof buf_, fmt, val);
            assert(static_cast<size_t>(length_) < sizeof buf_);
        }

// Explicit instantiations

        template Fmt::Fmt(const char *fmt, char val) ;

        template Fmt::Fmt(const char *fmt, short val);

        template Fmt::Fmt(const char *fmt, unsigned short val);

        template Fmt::Fmt(const char *fmt, int val);

        template Fmt::Fmt(const char *fmt, unsigned int val);

        template Fmt::Fmt(const char *fmt, long val);

        template Fmt::Fmt(const char *fmt, unsigned long val);

        template Fmt::Fmt(const char *fmt, long long val);

        template Fmt::Fmt(const char *fmt, unsigned long long val);

        template Fmt::Fmt(const char *fmt, float val);

        template Fmt::Fmt(const char *fmt, double val);
    }
}


#endif //RENDU_LOGMODEL_H
