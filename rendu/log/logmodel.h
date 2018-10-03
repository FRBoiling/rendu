//
// Created by boil on 18-10-3.
//

#ifndef RENDU_LOGMODEL_H
#define RENDU_LOGMODEL_H

#include <rendu/common/stringpiece.h>

namespace rendu {
    namespace log {

        const char* strerror_tl(int savedErrno);

        // helper class for known string length at compile time
        class T {
        public:
            T(const char *str, unsigned len)
                    : str_(str),
                      len_(len) {
                assert(strlen(str) == len_);
            }

            const char *str_;
            const unsigned len_;
        };


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


    }
}


#endif //RENDU_LOGMODEL_H
