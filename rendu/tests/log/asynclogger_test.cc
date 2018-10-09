//
// Created by boil on 18-10-9.
//
#include <rendu/log/AsyncLogger.h>
#include <rendu/log/Logger.h>
#include <sys/resource.h>
#include <rendu/thread/ThreadPool.h>

using namespace rendu;
using namespace rendu::log;

off_t kRollSize = 500 * 1000 * 1000;

AsyncLogger *g_asyncLog = NULL;

void asyncOutput(const char *msg, int len) {
    g_asyncLog->append(msg, len);
}

void bench(bool longLog) {
    Logger::setOutput(asyncOutput);

    int cnt = 0;
    const int kBatch = 1000;
    string empty = " ";
    string longStr(3000, 'X');
    longStr += " ";

    for (int t = 0; t < 30; ++t) {
        Timestamp start = Timestamp::now();
        for (int i = 0; i < kBatch; ++i) {
            LOG_INFO << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz "
                     << (longLog ? longStr : empty)
                     << cnt;
            ++cnt;
        }
        Timestamp end = Timestamp::now();
        printf("%f\n", timeDifference(end, start) * 1000000 / kBatch);
        struct timespec ts = {0, 500 * 1000 * 1000};
        nanosleep(&ts, NULL);
    }
}

void logInThread() {
    bench(true);
}

int main() {
    {
        // set max virtual memory to 2GB.
        size_t kOneGB = 1000 * 1024 * 1024;
        rlimit rl = {2 * kOneGB, 2 * kOneGB};
        setrlimit(RLIMIT_AS, &rl);
    }

    string strName = "async_logger_test";

    printf("pid = %d\n", getpid());

    char name[256] = {0};
    strncpy(name, strName.c_str(), sizeof name - 1);
    AsyncLogger log(::basename(name), kRollSize);
    log.start();
    g_asyncLog = &log;

    bool longLog = true;
//
//    thread::ThreadPool pool("pool");
//    pool.start(5);
//    pool.run(logInThread);
//    pool.run(logInThread);
//    pool.run(logInThread);
//    pool.run(logInThread);
//    pool.run(logInThread);

    bench(longLog);
}