#pragma once
#ifndef __THREAD_H__
#define __THREAD_H__

#include "pthread.h"
#include <functional>
using std::function;
class Thread
{
    pthread_t _pthId;
    bool _isrunning;
public:
    typedef function<void()> ThreadCallback;
    Thread(ThreadCallback cb);
    ~Thread();
    void start();
    void join();
private:
    static void * threadFunc(void * arg);
    ThreadCallback _cb;
};

#endif
