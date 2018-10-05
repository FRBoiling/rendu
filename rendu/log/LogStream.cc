//
// Created by boil on 18-10-3.
//

#include <rendu/common/StringUtil.h>
#include "LogStream.h"

using namespace rendu::log;

template<typename T>
void LogStream::formatInteger(T v) {
    if (buffer_.avail() >= kMaxNumericSize) {
        size_t len = util::convert(buffer_.current(), v);
        buffer_.add(len);
    }
}

LogStream &LogStream::operator<<(short v) {
    *this << static_cast<int>(v);
    return *this;
}

LogStream &LogStream::operator<<(unsigned short v) {
    *this << static_cast<unsigned int>(v);
    return *this;
}

LogStream &LogStream::operator<<(int v) {
    formatInteger(v);
    return *this;
}

LogStream &LogStream::operator<<(unsigned int v) {
    formatInteger(v);
    return *this;
}

LogStream &LogStream::operator<<(long v) {
    formatInteger(v);
    return *this;
}

LogStream &LogStream::operator<<(unsigned long v) {
    formatInteger(v);
    return *this;
}

LogStream &LogStream::operator<<(long long v) {
    formatInteger(v);
    return *this;
}

LogStream &LogStream::operator<<(unsigned long long v) {
    formatInteger(v);
    return *this;
}

LogStream &LogStream::operator<<(const void *p) {
    uintptr_t v = reinterpret_cast<uintptr_t>(p);
    if (buffer_.avail() >= kMaxNumericSize) {
        char *buf = buffer_.current();
        buf[0] = '0';
        buf[1] = 'x';
        size_t len = util::convertHex(buf + 2, v);
        buffer_.add(len + 2);
    }
    return *this;
}

// FIXME: replace this with Grisu3 by Florian Loitsch.
LogStream &LogStream::operator<<(double v) {
    if (buffer_.avail() >= kMaxNumericSize) {
        int len = snprintf(buffer_.current(), kMaxNumericSize, "%.12g", v);
        buffer_.add(len);
    }
    return *this;
}