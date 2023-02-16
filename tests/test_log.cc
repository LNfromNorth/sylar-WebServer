#include <iostream>
#include "sylar/log.h"
#include "sylar/util.h"

int main(void) {
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));
    
    sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
    logger->addAppender(file_appender);

    sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);

    // sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__, __LINE__, 0, sylar::GetThreadId(), 2, time(0)));
    // event->getSS() << "hello sylar log";

    // logger->log(sylar::LogLevel::DEBUG, event);

    SYLAR_LOG_INFO(logger) << "test macro info";
    SYLAR_LOG_DEBUG(logger) << "test macro debug";
    SYLAR_LOG_WARN(logger) << "test macro warn";

    SYLAR_LOG_FMT_DEBUG(logger, "test macro fmt debug %s", "hello");
    
    return 0;
}