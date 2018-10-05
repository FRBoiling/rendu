//
// Created by boil on 18-10-3.
//

#ifndef RENDU_LOG_LOGIMPL_H
#define RENDU_LOG_LOGIMPL_H

#include "LogLevel.h"
#include "LogStream.h"
#include <rendu/time/Timestamp.h>

using namespace rendu::time;

namespace rendu {
    namespace log {

        class LogImpl {
        public:
            LogImpl(LogLevel level, int old_errno, const SourceFile &file, int line);

            void formatTime();

            void finish();

            Timestamp time_;
            LogStream stream_;
            LogLevel level_;
            int line_;
            SourceFile basename_;
        };

    }
}

#endif //RENDU_LOG_LOGIMPL_H
