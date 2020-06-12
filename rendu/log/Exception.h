//
// Created by boil on 18-10-9.
//

#ifndef RENDU_LOG_EXCEPTION_H
#define RENDU_LOG_EXCEPTION_H

#include "rendu/common/types.h"
#include <exception>

namespace rendu
{
    namespace log
    {
        class Exception : public std::exception
        {
        public:
            Exception(string what);
            ~Exception() noexcept override = default;

            // default copy-ctor and operator= are okay.

            const char *what() const noexcept override
            {
                return message_.c_str();
            }

            const char *stackTrace() const noexcept
            {
                return stack_.c_str();
            }

        private:
            string message_;
            string stack_;
        };

    } // namespace log

} // namespace rendu

#endif // RENDU_LOG_EXCEPTION_H