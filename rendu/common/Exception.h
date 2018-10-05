//
// Created by boil on 18-10-4.
//

#ifndef RENDU_EXCEPTION_H
#define RENDU_EXCEPTION_H

#include "StringPiece.h"

namespace rendu{
    class Exception : public std::exception {
    public:
        explicit Exception(const char *what);

        explicit Exception(const string &what);

        virtual ~Exception() throw();

        virtual const char *what() const throw();

        const char *stackTrace() const throw();

    private:
        void fillStackTrace();

        string message_;
        string stack_;
    };
}

#endif //RENDU_EXCEPTION_H
