//
// Created by boil on 18-10-8.
//

#ifndef RENDU_FILEUTIL_H
#define RENDU_FILEUTIL_H

#include <rendu/common/StringPiece.h>
#include "ReadSmallFIle.h"

namespace rendu {
    namespace util {
        // read the file content, returns errno if error happens.
        template<typename String>
        int readFile(StringArg filename,
                     int maxSize,
                     String *content,
                     int64_t *fileSize = NULL,
                     int64_t *modifyTime = NULL,
                     int64_t *createTime = NULL) {
            ReadSmallFile file(filename);
            return file.readToString(maxSize, content, fileSize, modifyTime, createTime);
        }

        template int readFile(StringArg filename,
                              int maxSize,
                              string *content,
                              int64_t *, int64_t *, int64_t *);
    }
}


#endif //RENDU_FILEUTIL_H
