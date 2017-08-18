#include "Epollpoller.h"
#include "Acceptor.h"
#include "Socketutil.h"
#include <assert.h>
#include <unistd.h>
#include <iostream>
epollPoller::epollPoller(acceptor & caccept):
    _accept(caccept),
    _epollfd(createEpollFd()),
    _listenfd(_accept.fd()),
    _wakeupfd(createEventFd()),
    _islooping(0),
    _evelist(1024)
{
    addEpollRead(_epollfd,_listenfd);
    addEpollRead(_epollfd,_wakeupfd);
}
epollPoller::~epollPoller()
{
    if(_islooping)
        unloop();
    close(_epollfd);
}
void epollPoller::loop()
{
    _islooping = 1;
    while(_islooping)
    {
        waitEpollFd();
    }
}
void epollPoller::unloop()
{
    if(_islooping)
        _islooping = 0;
}
void epollPoller::runinloop(const functor & cb)
{
    MutexLockGuard mlg(_mutex);
    _pendinffunctors.push_back(cb);
    wakeup();
}
void epollPoller::pendingfunctor()
{
    vector<functor> tasktemp;
    MutexLockGuard mlg(_mutex);
    tasktemp.swap(_pendinffunctors);
    for(auto & it :tasktemp)
        it();
}
void epollPoller::wakeup()
{
    uint64_t one = 1;
    if(::write(_wakeupfd,&one,sizeof(one)) != sizeof(one))
        perror("epollPoller wakeup");
}
void epollPoller::handlread()
{
    uint64_t one  =1;
    if(::read(_wakeupfd,&one,sizeof(one)) != sizeof(one))
        perror("epollPoller handleread");
}
void epollPoller::setConnectionCb( epollpollerCallback cb )
{
    _onConnectioncb = cb;
}
void epollPoller::setMessageCb( epollpollerCallback cb )
{
    _onMessagecb = cb;
}
void epollPoller::setCloseCb(epollpollerCallback cb)
{
    _onClosecb = cb;
}
void epollPoller::waitEpollFd()
{
    int nready ;
    do{
        nready = epoll_wait(_epollfd, &(*_evelist.begin()),_evelist.size(),5000);
    }while(nready == -1 && EINTR == errno);
    if(nready == -1)
    {
        perror("err epoll wait");
        exit(EXIT_FAILURE);
    }else if(nready == 0)
    {
        std::cout<<"epoll wait timeout\n";
    }else
    {
        if((size_t)nready == _evelist.size())
        {
            _evelist.resize(2*nready);
        }
        for(int i = 0; i != nready; ++i)
        {
            if(_evelist[i].data.fd ==_listenfd && (_evelist[i].events & EPOLLIN))
            {
                handleConnection();
            }else if(_evelist[i].data.fd == _wakeupfd)
            {
                printf("execute wakeup\n");
                if(_evelist[i].events & EPOLLIN)
                {
                    handlread();
                    pendingfunctor();
                }
            }else{
                if(_evelist[i].events & EPOLLIN){
                    handleMessage(_evelist[i].data.fd);
		}
            }
        }
    }
}
void epollPoller::handleConnection()
{
    int peerfd = _accept.accept();
    addEpollRead(_epollfd,peerfd);
    TcpConnectionPtr conn(new TcpConnection(peerfd,this));
    conn->SetConnectionCb(_onConnectioncb);
    conn->SetMessageCb(_onMessagecb);
    conn->SetCloseCb(_onClosecb);
    std::pair<connectionmap::iterator,bool> ret;
    ret = _connmap.insert(std::make_pair(peerfd,conn));
    assert(ret.second);
    (void)ret;
    conn->handleConnectionCb();
}
void epollPoller::handleMessage(int peerfd )
{
    bool isclosed = isConnectionclosed(peerfd);
    auto it = _connmap.find(peerfd);
    assert(it != _connmap.end()); //20170726 12:23
    if(isclosed)
    {
        it->second->handleCloseCb();
        delEpollRead(_epollfd,peerfd);
        _connmap.erase(peerfd);
    }else
    {
	it->second->handleMessageCb();
    }
}


