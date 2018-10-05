//
// Created by boil on 18-10-3.
//

#ifndef RENDU_LOG_LOGLEVEL_H
#define RENDU_LOG_LOGLEVEL_H

namespace rendu{
    namespace log{

        enum LogLevel {
            TRACE,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            NUM_LOG_LEVELS,
        };

//        const char* LogLevelName[NUM_LOG_LEVELS] =
//                {
//                        "TRACE ",
//                        "DEBUG ",
//                        "INFO  ",
//                        "WARN  ",
//                        "ERROR ",
//                        "FATAL ",
//                };
        const char LogLevelName[NUM_LOG_LEVELS][8] =
                {
                        "TRACE ",
                        "DEBUG ",
                        "INFO  ",
                        "WARN  ",
                        "ERROR ",
                        "FATAL ",
                };
    }
}

#endif //RENDU_LOG_LOGLEVEL_H
