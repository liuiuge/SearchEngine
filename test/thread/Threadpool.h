#pragma once
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "Buffer.h"
#include <vector>
using std::vector;

class Thread;

class Threadpool
{
    size_t _threadsNum;
    Buffer _buf;
    vector<Thread *> _vecthreads;
    bool _isexit;
    void threadpoolFunc();
public:
    typedef function<void()> Task;
    Threadpool(size_t threadsNum, size_t bufnum);
    ~Threadpool();
    void start();
    void stop();
    void addtask(Task task);
private:
    Task getTask();
};

#endif
