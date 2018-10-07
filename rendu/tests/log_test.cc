//
// Created by boil on 18-10-3.
//

#include <rendu/log/Logger.h>
#include <rendu/thread/ThreadPool.h>

using namespace rendu;
using namespace rendu::log;
using namespace rendu::thread;

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
    LOG_INFO << "Hello NYT";
    LOG_WARN << "World NYT";
    LOG_ERROR << "Error NYT";




}