// TcpClient destructs in a different thread.

#include "../includes/EventLoopThread.h"
#include "../includes/TcpClient.h"

#include "rendu/base/includes/Logger.h"

using namespace rendu;
using namespace rendu::net;

int main(int argc, char *argv[])
{
    Logger::setLogLevel(Logger::DEBUG);

    EventLoopThread loopThread;
    {
        InetAddress serverAddr("127.0.0.1", 1234); // should succeed
        TcpClient client(loopThread.startLoop(), serverAddr, "TcpClient");
        client.connect();
        CurrentThread::sleepUsec(500 * 1000); // wait for connect
        client.disconnect();
    }

    CurrentThread::sleepUsec(1000 * 1000);
}
