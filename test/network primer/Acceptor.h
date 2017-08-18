#pragma once
#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "Inetaddress.h"
#include "Socket.h"
class acceptor
{
    Socket _listensock;
    inetAddress _addr;
    void bind();
    void listen();
    void setReuseAddr(bool on);
    void setReusePort(bool on);
public:
    acceptor(const int fd,const inetAddress & addr);
    void ready();
    int accept();
    int fd()const;
};

#endif
