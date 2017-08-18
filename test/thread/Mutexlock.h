#pragma once
#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>

class Mutex_lock{
    pthread_mutex_t _mutex;
    bool _is_locked;
public:
    Mutex_lock()
        :_is_locked(0)
    {
        pthread_mutex_init(&_mutex, NULL);
    }
    ~Mutex_lock()
    {
        pthread_mutex_destroy(&_mutex);
    }
    void lock()
    {
        pthread_mutex_lock(&_mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }
    pthread_mutex_t * getMutexPtr()
    {
        return &_mutex;
    }
};
class MutexLockGuard
{
    Mutex_lock & _mutex;
public:
    MutexLockGuard(Mutex_lock & mutex1)
        :_mutex(mutex1)
    {
        _mutex.lock();
    }
    ~MutexLockGuard()
    {
        _mutex.unlock();
    }

};

#endif
