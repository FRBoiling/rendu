//
// Created by boil on 20-5-11.
//

#ifndef RENDU_NET_EPOLLPOLLER_H
#define RENDU_NET_EPOLLPOLLER_H

#include "Poller.h"

#include <vector>

struct epoll_event;

namespace rendu
{
    namespace net
    {

        ///
        /// IO Multiplexing with epoll(4).
        ///
        class EPollPoller : public Poller
        {
        public:
            EPollPoller(EventLoop *loop);
            virtual ~EPollPoller();

            virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels);
            virtual void updateChannel(Channel *channel);
            virtual void removeChannel(Channel *channel);

        private:
            static const int kInitEventListSize = 16;

            static const char *operationToString(int op);

            void fillActiveChannels(int numEvents,
                                    ChannelList *activeChannels) const;
            void update(int operation, Channel *channel);

            typedef std::vector<struct epoll_event> EventList;

            int epollfd_;
            EventList events_;
        };

    } // namespace net
} // namespace rendu

#endif //RENDU_NET_EPOLLPOLLER_H
