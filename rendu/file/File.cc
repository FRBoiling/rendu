//
// Created by boil on 20-05-28.
//

#include "File.h"
#include <stdio.h>  // snprintf
#include <stdexcept>

using namespace rendu;

bool File::valid() const { return fp_; }

string File::readBytes(int n)
{
    char buf[n];
    ssize_t nr = ::fread(buf, 1, n, fp_);
    if (nr != n)
        throw logic_error("no enough data");
    return string(buf, n);
}

int32_t File::readInt32()
{
    int32_t x = 0;
    ssize_t nr = ::fread(&x, 1, sizeof(int32_t), fp_);
    if (nr != sizeof(int32_t))
        throw logic_error("bad int32_t data");
    return be32toh(x);
}

uint8_t File::readUInt8()
{
    uint8_t x = 0;
    ssize_t nr = ::fread(&x, 1, sizeof(uint8_t), fp_);
    if (nr != sizeof(uint8_t))
        throw logic_error("bad uint8_t data");
    return x;
}