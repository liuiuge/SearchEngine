#pragma once
#ifndef __EPOLLPOLLER_H__
#define __EPOLLPOLLER_H__

#include "TcpConnection.h"
#include "Mutexlock.h"
#include <sys/epoll.h>
#include <vector>
using std::vector;
#include <map>
using std::map;

class acceptor;
class epollPoller
{
public:
    typedef TcpConnection::TcpConnectionCallback epollpollerCallback;
    typedef std::function<void()> functor;
    epollPoller(acceptor & caccept);
    ~epollPoller();
    void loop();
    void unloop();
    void runinloop(const functor & cb);
    void pendingfunctor();
    void wakeup();
    void handlread();
    void setConnectionCb(epollpollerCallback cb);
    void setMessageCb(epollpollerCallback cb);
    void setCloseCb(epollpollerCallback cb);
private:
    void waitEpollFd();
    void handleConnection();
    void handleMessage(int peerfd);

    acceptor & _accept;
    int _epollfd;
    int _listenfd;
    int _wakeupfd;
    bool _islooping;
    Mutex_lock _mutex;
    vector<functor> _pendinffunctors;

    typedef vector<struct epoll_event> eventlist;
    eventlist _evelist;
    typedef map<int,TcpConnectionPtr> connectionmap;
    connectionmap _connmap;
    epollpollerCallback _onConnectioncb;
    epollpollerCallback _onMessagecb;
    epollpollerCallback _onClosecb;
};

#endif
