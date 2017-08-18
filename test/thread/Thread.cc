#include "Thread.h"
Thread::Thread(ThreadCallback cb):
    _pthId(0),
    _isrunning(0),
    _cb(cb)
{}
Thread::~Thread()
{
    if(_isrunning)
    {
        _isrunning = false;
        pthread_detach(_pthId);
    }
}
void Thread::start()
{
    pthread_create(&_pthId ,NULL, threadFunc, this);
    _isrunning = 1;
}
void Thread::join()
{
    pthread_join(_pthId, NULL);
}
void *Thread::threadFunc(void * arg)
{
    Thread * process = static_cast<Thread *>(arg);
    if(process){
        process->_cb();
	return process;
    }
    return NULL;
}
#ifdef HELLO
{
    pthread_t pthId;
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
