//
// Created by boil on 20-4-24.
//

#include "Poller.h"

using namespace rendu::net;

Poller::Poller(EventLoop* loop)
        : ownerLoop_(loop)
{
}

Poller::~Poller()
{
}

bool Poller::hasChannel(Channel* channel) const
{
    assertInLoopThread();
    ChannelMap::const_iterator it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}