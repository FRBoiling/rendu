//
// Created by boil on 20-5-28.
//

#ifndef RENDU_FILE_READSMALLFILE_H
#define RENDU_FILE_READSMALLFILE_H

namespace rendu
{
    // read small file < 64KB
    class ReadSmallFile : noncopyable
    {
    public:
        SmallFile(StringArg filename);
        ~SmallFile();

        // return errno
        template <typename String>
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

} // namespace rendu
#endif //RENDU_FILE_READSMALLFILE_H