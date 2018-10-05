//
// Created by boil on 18-10-3.
//

#include <rendu/log/Logger.h>
using namespace rendu::log;

int main() {
    LOG_TRACE << "trace";
    LOG_DEBUG << "debug";
    LOG_INFO << "Hello";
    LOG_WARN << "World";
    LOG_ERROR << "Error";
}