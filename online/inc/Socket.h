#pragma once
#ifndef __SOCKET_H__
#define __SOCKET_H__
#include "Inetaddress.h"
class Socket
{
    int _fd;
public:
    Socket(int);
    Socket();
    void shutdownWrite();
    void nonblock();
    int fd()const;
    inetAddress getlocaladdress(int sockfd);
    inetAddress getpeeraddress(int sockfd);
};

#endif
