#include "Acceptor.h"
#include "Socketutil.h" //20170726 11:55
#include <iostream>

acceptor::acceptor(const int fd,const inetAddress & addr):
    _listensock(fd),
    _addr(addr)
{}
void acceptor::ready()
{
    setReuseAddr(1);
    setReusePort(1);
    bind();
    listen();
}
void acceptor::setReuseAddr(bool on)
{
    int flag = on?1:0;
    if(setsockopt(_listensock.fd(),SOL_SOCKET,
        SO_REUSEADDR,&flag,
        static_cast<socklen_t>(sizeof(flag))) == -1)
    {
        perror("set socket reuseaddress error");
        close(_listensock.fd());
        exit(EXIT_FAILURE);
    }
}
void acceptor::setReusePort(bool on)
{
    int flag = on?1:0;
    if(setsockopt(_listensock.fd(),SOL_SOCKET,
        SO_REUSEPORT,&flag,
        static_cast<socklen_t>(sizeof(flag))) == -1)
    {
        perror("set socket resueport error");
        close(_listensock.fd());
        exit(EXIT_FAILURE);
    }
}
void acceptor::bind()
{
    if(-1 == ::bind(_listensock.fd(),
            (const struct sockaddr*)_addr.getAddressPtr(),
            sizeof(inetAddress)))
    {
        perror("bind socket address err");
        close(_listensock.fd());
        exit(EXIT_FAILURE);
    }
    std::cout<<">bind\n";
}
void acceptor::listen()
{
    if(-1 == ::listen(_listensock.fd(),5))
    {
        perror("listen socket err");
        close(_listensock.fd());
        exit(EXIT_FAILURE);
    }
    std::cout<<">listen\n";
}
int acceptor::accept()
{
    int peerfd = ::accept(_listensock.fd(),NULL,NULL);
    if(-1 == peerfd)
    {
        perror("accept err");
        close(_listensock.fd());
        exit(EXIT_FAILURE);
    }
    std::cout<<">accept"<<peerfd<<"\n";
    return peerfd;
}
int acceptor::fd() const
{
    return _listensock.fd();
}
