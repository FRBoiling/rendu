#include <rendu/common/Types.h>
#include <rendu/log/Logger.h>
#include <rendu/net/TcpServer.h>
#include <rendu/net/EventLoop.h>
#include <rendu/thread/Thread.h>
#include <rendu/thread/CurrentThread.h>

using namespace rendu;
using namespace rendu::net;
using namespace rendu::time;
using namespace rendu::log;
using namespace rendu::thread;

void onConnection(const TcpConnectionPtr& conn)
{
    if (conn->connected())
    {
        conn->setTcpNoDelay(true);
    }
}

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp)
{
    conn->send(buf);
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage: server <address> <port> <threads>\n");
    }
    else
    {
        LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
        Logger::setLogLevel(LogLevel::WARN);

        LOG_DEBUG<<"";
        const char* ip = argv[1];
        uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
        InetAddress listenAddr(ip, port);
        int threadCount = atoi(argv[3]);

        EventLoop loop;

        TcpServer server(&loop, listenAddr, "PingPong");

        server.setConnectionCallback(onConnection);
        server.setMessageCallback(onMessage);

        if (threadCount > 1)
        {
            server.setThreadNum(threadCount);
        }

        server.start();

        loop.loop();
    }
}