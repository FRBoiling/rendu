//
// Created by boil on 20-05-28.
//

#ifndef RENDU_FILE_APPENDFILE_H
#define RENDU_FILE_APPENDFILE_H

#include "rendu/base/types.h"
#include "rendu/base/noncopyable.h"
#include "rendu/base/stringpiece.h"

namespace rendu
{
    // not thread safe
    class AppendFile : noncopyable
    {
    public:
        explicit AppendFile(StringArg filename);

        ~AppendFile();

        void append(const char *logline, size_t len);

        void flush();

        off_t writtenBytes() const { return writtenBytes_; }

    private:
        size_t write(const char *logline, size_t len);

        FILE *fp_;
        char buffer_[64 * 1024];
        off_t writtenBytes_;
    };

} // namespace rendu

#endif //RENDU_FILE_APPENDFILE_H