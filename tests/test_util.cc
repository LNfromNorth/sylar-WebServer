#include "sylar/sylar.h"
#include <iostream>
#include <assert.h>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_assert() {
    SYLAR_LOG_INFO(g_logger) << sylar::BacktraceToString(10, 2, " ");
    SYLAR_ASSERT2( 0 == 1, "abcdefg");
}

int main() {
    test_assert();
    SYLAR_LOG_INFO(g_logger) << "Hello World";
    return 0;
}

