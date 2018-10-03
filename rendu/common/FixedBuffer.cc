//
// Created by boil on 18-10-3.
//

#include "FixedBuffer.h"

using namespace rendu;

template<int SIZE>
const char *FixedBuffer<SIZE>::debugString() {
    *cur_ = '\0';
    return data_;
}

template<int SIZE>
void FixedBuffer<SIZE>::cookieStart() {
}

template<int SIZE>
void FixedBuffer<SIZE>::cookieEnd() {
}
