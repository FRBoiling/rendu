//
// Created by boil on 18-10-8.
//

#ifndef RENDU_READSMALLFILE_H
#define RENDU_READSMALLFILE_H


#include <rendu/common/noncopyable.h>
#include <rendu/common/StringPiece.h>

namespace rendu{
    namespace util{

// read small file < 64KB
        class ReadSmallFile : rendu::noncopyable {
        public:
            ReadSmallFile(StringArg filename);

            ~ReadSmallFile();

            // return errno
            template<typename String>
            int readToString(int maxSize,
                             String *content,
                             int64_t *fileSize,
                             int64_t *modifyTime,
                             int64_t *createTime);

            /// Read at maxium kBufferSize into buf_
            // return errno
            int readToBuffer(int *size);

            const char *buffer() const { return buf_; }

            static const int kBufferSize = 64 * 1024;

        private:
            int fd_;
            int err_;
            char buf_[kBufferSize];
        };


    }
}


#endif //RENDU_READSMALLFILE_H
