#include "Threadpool.h"
#include "Thread.h"
#include <stdio.h>
#include <unistd.h>
Threadpool::Threadpool(size_t threadsNum, size_t bufnum):
    _threadsNum(threadsNum),
    _buf(bufnum),
    _isexit(0)
{}
Threadpool::~Threadpool()
{
    if(!_isexit)
        stop();
}
void Threadpool::start()
{
    for(size_t idx = 0; idx != _threadsNum; ++idx)
    {
        Thread * pthread = new Thread(
            std::bind(&Threadpool::threadpoolFunc,this));
        _vecthreads.push_back(pthread);
    }
    std::vector<Thread *>::iterator it;
    for(it = _vecthreads.begin(); it != _vecthreads.end(); ++it)
    {
        (*it)->start();
    }
    printf("Threadpool start\n");
}
void Threadpool::stop()
{
    if(!_isexit)
    {
        while(!_buf.empty())
           sleep(1);
	_isexit = 1;
    
        _buf.wakeup_empty();
        vector<Thread *>::iterator it;
        for(it = _vecthreads.begin(); it!= _vecthreads.end(); ++it)
        {
            (*it)->join();
            delete (*it);
        }
        _vecthreads.clear();
    }
}
void Threadpool::addtask(Task task)
{
    printf("Threadpool::addTask()\n");
    _buf.push(task);
}
Threadpool::Task Threadpool::getTask()
{
    return _buf.pop();
}
void Threadpool::threadpoolFunc()
{
    while(!_isexit)
    {
        Task task = getTask();
        if(task)
            task();
    }
}

#ifdef HELLO
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
