#pragma once
#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "Mutexlock.h"

class Condition
{
    pthread_cond_t _cond;
    Mutex_lock & _mutex;
public:
    Condition(Mutex_lock & mutex1)
        :_mutex(mutex1)
    {
        pthread_cond_init(&_cond,NULL);
    }
    ~Condition()
    {
        pthread_cond_destroy(&_cond);
    }
    void wait()
    {
        pthread_cond_wait(&_cond,_mutex.getMutexPtr());
    }
    void notify()
    {
        pthread_cond_signal(&_cond);
    }
    void notifyall()
    {
        pthread_cond_broadcast(&_cond);
    }

};

#endif
