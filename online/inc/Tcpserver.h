#pragma once
#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "Inetaddress.h"
#include "Configuration.h"
#include "Epollpoller.h"
#include "Acceptor.h"

class Tcpserver
{
    acceptor _acc;
    epollPoller _epollfd;
public:
    typedef TcpConnection::TcpConnectionCallback TcpserverCallback;
    Tcpserver(unsigned short port);
    Tcpserver(const char * IP, unsigned short port);
    void start();
    void stop();
    void setConnectionCallback(TcpserverCallback cb);
    void setMessageCallback(TcpserverCallback cb);
    void setCloseCallback(TcpserverCallback cb);
};

#endif
