#include "../includes/LogFile.h"
#include "../includes/Logger.h"

#include <unistd.h>

std::unique_ptr<rendu::LogFile> g_logFile;

void outputFunc(const char *msg, int len)
{
    g_logFile->append(msg, len);
}

void flushFunc()
{
    g_logFile->flush();
}

int main(int argc, char *argv[])
{
    char name[256] = {'\0'};
    strncpy(name, argv[0], sizeof name - 1);
    g_logFile.reset(new rendu::LogFile(::basename(name), 200 * 1000));
    rendu::Logger::setOutput(outputFunc);
    rendu::Logger::setFlush(flushFunc);

    rendu::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

    for (int i = 0; i < 10000; ++i)
    {
        LOG_INFO << line << i;

        usleep(1000);
    }
}