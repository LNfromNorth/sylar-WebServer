#ifndef __SYLAR_IOMANAGER_H
#define __SYLAR_IOMANAGER_H

#include "sylar/scheduler.h"
#include "sylar/timer.h"

namespace sylar {

class IOManager : public Scheduler, public TimerManager {
public:
    typedef std::shared_ptr<IOManager> ptr;
    typedef RWMutex RWMutexType;

    enum Event {
        NONE  = 0x0,
        READ  = 0x1,  // EPOLLIN
        WRITE = 0x4,  // EPOLLOUT
    };

private:
    struct FdContext {
        typedef Mutex MutexType;
        struct EventContext {
            Scheduler* scheduler = nullptr;      // 待执行的 scheduler
            Fiber::ptr fiber;                    // 事件协程
            std::function<void()> cb;            // 时间的回调函数
        };

        EventContext& getContext(Event event);
        void resetContext(EventContext& ctx);
        void triggerEvent(Event event);

        EventContext read;       // 读事件
        EventContext write;      // 写事件
        int fd = 0;              // 事件关联的句柄
        Event events = NONE;     // 已经注册的事件
        MutexType mutex;
    };

public:
    IOManager(size_t threads = 1, bool use_caller = true, const std::string& name = "");
    ~IOManager();

    // 0 success, -1 error
    int addEvent(int fd, Event event, std::function<void()> cb = nullptr);
    bool delEvent(int fd, Event event);
    bool cancelEvent(int fd, Event event);

    bool cancelAll(int fd);

    static IOManager* GetThis();

protected:
    void tickle() override;         // 有协程需要执行的时候调用
    bool stopping() override;       // 决定模块是否可以终止
    void idle() override;           // 没有协程的时候进入

    bool stopping(uint64_t& timeout);
    void onTimerInsertedAtFront() override;

    void contextResize(size_t size);
private:
    int m_epfd = 0;
    int m_tickleFds[2];

    std::atomic<size_t> m_pendingEventCount = {0};
    RWMutexType m_mutex;
    std::vector<FdContext*> m_fdContexts;
};

}

#endif
