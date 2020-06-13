//
// Created by boil on 18-10-3.
//

#ifndef RENDU_ILOG_H
#define RENDU_ILOG_H

#include "Interface.h"

namespace rendu
{
    Interface ILog
    {
        public:
        ILog();
        ~ILog();

    public:
        virtual void initLog() = 0;
    };
}

#endif //RENDU_ILOG_H
