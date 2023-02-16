#ifndef __SYLAR_SINGLETON_H
#define __SYLAR_SINGLETON_H

#include <memory>

namespace sylar {

template<class T, class X = void, int N = 0>
class Singleton {
public:
    static T* GetInstance() {
        // 这里使用 static 修饰，使用同一个对象
        static T v;
        return &v;
    }
};

template<class T, class X = void, int N = 0>
class SingletonPtr {
public:
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> v(new T);
        return v;
    }
};

}

#endif
