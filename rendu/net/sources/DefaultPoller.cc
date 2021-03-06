//
// Created by boil on 20-5-11.
//

#include <stdlib.h>
#include "../includes/PollPoller.h"
#include "../includes/EPollPoller.h"

using namespace rendu;
using namespace rendu::net;

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
    if (::getenv("RENDU_USE_POLL"))
    {
        return new PollPoller(loop);
    }
    else
    {
        return new EPollPoller(loop);
    }
}
