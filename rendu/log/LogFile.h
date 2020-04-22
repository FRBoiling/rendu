//
// Created by boil on 18-10-8.
//

#ifndef RENDU_LOGFILE_H
#define RENDU_LOGFILE_H

#include <rendu/common/noncopyable.h>
#include <memory>
#include <rendu/thread/Mutex.h>
#include <rendu/util/AppendFile.h>
#include <rendu/common/Types.h>

namespace rendu{
    namespace log{
        class LogFile : rendu::noncopyable
        {
        public:
            LogFile(const string& basename,
                    off_t rollSize,
                    bool threadSafe = true,
                    int flushInterval = 3,
                    int checkEveryN = 1024);
            ~LogFile();

            void append(const char* logline, int len);
            void flush();
            bool rollFile();

        private:
            void append_unlocked(const char* logline, int len);

            static string getLogFileName(const string& basename, time_t* now);

            const string basename_;
            const off_t rollSize_;
            const int flushInterval_;
            const int checkEveryN_;

            int count_;

            std::unique_ptr<thread::MutexLock> mutex_;
            time_t startOfPeriod_;
            time_t lastRoll_;
            time_t lastFlush_;
            std::unique_ptr<util::AppendFile> file_;

            const static int kRollPerSeconds_ = 60*60*24;
        };

    }
}


#endif //RENDU_LOGFILE_H
