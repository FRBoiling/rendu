//
// Created by boil on 18-10-9.
//
#include "Exception.h"
#include "rendu/thread/CurrentThread.h"
namespace rendu
{
    namespace log
    {
        Exception::Exception(string msg)
            : message_(std::move(msg)),
              stack_(CurrentThread::stackTrace(/*demangle=*/false))
        {
        }
    } // namespace log
} // namespace rendu
