//
// Created by boil on 18-10-3.
//

#include <rendu/log/Logger.h>
#include <rendu/thread/ThreadPool.h>
#include <rendu/log/LogFile.h>

using namespace rendu;
using namespace rendu::log;
using namespace rendu::thread;

int g_total;
FILE* g_file;
std::unique_ptr<LogFile> g_logFile;

void dummyOutput(const char* msg, int len)
{
    g_total += len;
    if (g_file)
    {
        fwrite(msg, 1, len, g_file);
    }
    else if (g_logFile)
    {
        g_logFile->append(msg, len);
    }
}

void bench(const char* type)
{
    Logger::setOutput(dummyOutput);
    Timestamp start(Timestamp::now());
    g_total = 0;

    int n = 1000*1000;
    const bool kLongLog = false;
    string empty = " ";
    string longStr(3000, 'X');
    longStr += " ";
    for (int i = 0; i < n; ++i)
    {
        LOG_INFO << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz"
                 << (kLongLog ? longStr : empty)
                 << i;
    }
    Timestamp end(Timestamp::now());
    double seconds = timeDifference(end, start);
    printf("%12s: %f seconds, %d bytes, %10.2f msg/s, %.2f MiB/s\n",
           type, seconds, g_total, n / seconds, g_total / seconds / (1024 * 1024));
}


void logInThread()
{
    LOG_INFO << "logInThread";
    usleep(1000);
}

int main() {
    getppid(); // for ltrace and strace

    Logger::init();

    ThreadPool pool("pool");
    pool.start(5);
    pool.run(logInThread);
    pool.run(logInThread);
    pool.run(logInThread);
    pool.run(logInThread);
    pool.run(logInThread);

    Logger::setLogLevel(TRACE);
    LOG_TRACE << "trace";
    LOG_DEBUG << "debug";
    LOG_INFO << "info";
    LOG_WARN << "warn";
    LOG_ERROR << "Error";

    sleep(1);
    bench("nop");

    char buffer[64*1024];

    g_file = fopen("/dev/null", "w");
    setbuffer(g_file, buffer, sizeof buffer);
    bench("/dev/null");
    fclose(g_file);

    g_file = fopen("/tmp/log", "w");
    setbuffer(g_file, buffer, sizeof buffer);
    bench("/tmp/log");
    fclose(g_file);

    g_file = NULL;
    g_logFile.reset(new LogFile("test_log_st", 500*1000*1000, false));
    bench("test_log_st");

    g_logFile.reset(new LogFile("test_log_mt", 500*1000*1000, true));
    bench("test_log_mt");

    g_logFile.reset();

    g_file = stdout;

    sleep(1);
    time::TimeZone beijing(8*3600, "CST");
    Logger::setTimeZone(beijing);
    LOG_TRACE << "trace CST";
    LOG_DEBUG << "debug CST";
    LOG_INFO << "info CST";
    LOG_WARN << "warn CST";
    LOG_ERROR << "Error CST";

    sleep(1);
    time::TimeZone newyork("/usr/share/zoneinfo/America/New_York");
    Logger::setTimeZone(newyork);
    LOG_TRACE << "trace NYT";
    LOG_DEBUG << "debug NYT";
    LOG_INFO << "info NYT";
    LOG_WARN << "warn NYT";
    LOG_ERROR << "Error NYT";

    g_file = NULL;
}