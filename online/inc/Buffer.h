#pragma once
#ifndef __BUFFER_H__
#define __BUFFER_H__
#include "Condition.h"
#include <queue>
using std::queue;
#include <functional>
using std::function;

class Buffer
{
    Mutex_lock _mutex;
    Condition _notempty;
    Condition _notfull;
    typedef std::function<void()> Task;
    size_t _size;
    queue<Task> _que;
    bool _flag;
public:
    Buffer(int);
    bool empty();
    bool full();
    void push(const Task & );
    Task pop();
    void wakeup_empty();
};

#endif
