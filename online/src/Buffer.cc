#include "Buffer.h"
Buffer::Buffer(int size)
    :_mutex()
    ,_notempty(_mutex)
    ,_notfull(_mutex)
    ,_size(size)
    ,_flag(1)
{}
bool Buffer::empty()
{
    return _que.empty();
}
bool Buffer::full()
{
    return _que.size() == _size;
}
void Buffer::push(const Task & elem)
{
//    _mutex.lock();
    MutexLockGuard mlg(_mutex);
    while(full())
        _notfull.wait();
    _que.push(elem);
    _notempty.notify();
//    _mutex.unlock();
}
Buffer::Task Buffer::pop()
{
    MutexLockGuard mlg(_mutex);
    while(empty() && _flag)
        _notempty.wait();
    if(_flag == 0)
        return NULL;
    Task value = _que.front();
    _que.pop();
    _notfull.notify();
    return value;
}
void Buffer::wakeup_empty()
{
    _flag = 0;
    _notfull.notifyall();
}



#ifdef HELLO
    Mutex_lock _mutex;
    Condition _notempty;
    Condition _notfull;
    typedef std::function<void()> Task;
    size_t _size;
    queue<Task> _que;
    bool _flag;
    Buffer(int);
    bool empty();
    bool full();
    void push(Task);
    Task & pop();
    void wakeup_empty();
#endif
