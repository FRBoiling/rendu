//
// Created by boil on 20-4-17.
//

#ifndef RENDU_NET_ACCEPTOR_H
#define RENDU_NET_ACCEPTOR_H

#include <boost/function.hpp>
#include "rendu/base/rendu_base.h"
#include "SocketsOps.h"
#include "InetAddress.h"
#include "EventLoop.h"
#include "Channel.h"
#include "Socket.h"

namespace rendu
{
    namespace net
    {
        ///
        /// Acceptor of incoming TCP connections.
        ///
        class Acceptor : Noncopyable
        {
        public:
            typedef boost::function<void(int sockfd,
                                         const InetAddress &)>
                NewConnectionCallback;

            Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);

            ~Acceptor();

            void setNewConnectionCallback(const NewConnectionCallback &cb) { newConnectionCallback_ = cb; }

            bool listenning() const { return listenning_; }

            void listen();

        private:
            void handleRead();

            EventLoop *loop_;
            Socket acceptSocket_;
            Channel acceptChannel_;
            NewConnectionCallback newConnectionCallback_;
            bool listenning_;
            int idleFd_;
        };

    } // namespace net
} // namespace rendu

#endif //RENDU_NET_ACCEPTOR_H
