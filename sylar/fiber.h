#ifndef __SYLAR_FIBER_H
#define __SYLAR_FIBER_H

#include <ucontext.h>
#include <memory>
#include <functional>

#include "sylar/thread.h"

// ucontext.h lib 
namespace sylar {

class Scheduler;
class Fiber : public std::enable_shared_from_this<Fiber> {
friend class Scheduler;
public:
    typedef std::shared_ptr<Fiber> ptr;

    enum State {
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY,
        EXCEPT
    };
private:
    Fiber();
public:
    Fiber(std::function<void()> cb, size_t stacksize = 0, bool use_caller = false);
    ~Fiber();

    // 重置协程函数，并重置状态
    void reset(std::function<void()> cb);
    void call();
    void back();
    // 切换到当前协程
    void swapIn();
    // 切换到后台运行
    void swapOut();

    uint64_t getId() const { return m_id;}
    void setState(State state) {
        m_state = state;
    }
    State getState() const { return m_state;}
public:
    static void SetThis(Fiber* f);
    // 返回当前协程
    static Fiber::ptr GetThis();
    // 协程切换到后台，并且设置为 Ready 状态
    static void YieldToReady();
    // 协程切换到后台，并且设置为 Hold 状态
    static void YieldToHold();
    // 总协程数
    static uint64_t TotalFibers();
    
    static void MainFunc();
    static void CallerMainFunc();
    static uint64_t GetFiberId();

private:
    uint64_t m_id = 0;
    uint32_t m_stacksize = 0;
    State m_state = INIT;

    ucontext_t m_ctx;
    void* m_stack = nullptr;

    std::function<void()> m_cb;
};

}

#endif
