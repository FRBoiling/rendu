//
// Created by boil on 20-5-11.
//

#ifndef RENDU_POLLPOLLER_H
#define RENDU_POLLPOLLER_H

#include <vector>
#include <rendu/net/Poller.h>

struct pollfd;

namespace rendu
{
    namespace net
    {

///
/// IO Multiplexing with poll(2).
///
        class PollPoller : public Poller
        {
        public:

            PollPoller(EventLoop* loop);
            virtual ~PollPoller();

            virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels);
            virtual void updateChannel(Channel* channel);
            virtual void removeChannel(Channel* channel);

        private:
            void fillActiveChannels(int numEvents,
                                    ChannelList* activeChannels) const;

            typedef std::vector<struct pollfd> PollFdList;
            PollFdList pollfds_;
        };

    }
}

#endif //RENDU_POLLPOLLER_H
