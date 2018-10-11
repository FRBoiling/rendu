//
// Created by boil on 18-10-8.
//

#ifndef RENDU_APPENDFILE_H
#define RENDU_APPENDFILE_H

#include <rendu/common/noncopyable.h>
#include <sys/types.h>  // for off_t
#include "rendu/common/StringPiece.h"

namespace rendu {
    namespace util {

        // not thread safe
        class AppendFile : rendu::noncopyable {
        public:
            explicit AppendFile(StringArg filename);

            ~AppendFile();

            void append(const char *logline, const size_t len);

            void flush();

            off_t writtenBytes() const { return writtenBytes_; }

        private:

            size_t write(const char *logline, size_t len);

            FILE *fp_;
            char buffer_[64 * 1024];
            off_t writtenBytes_;
        };
    }
}

#endif //RENDU_APPENDFILE_H
