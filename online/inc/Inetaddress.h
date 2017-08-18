#pragma once
#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include "netinet/in.h"
#include <string>
using std::string;

class inetAddress
{
    struct sockaddr_in _addr;
public:
    inetAddress(unsigned short port);
    inetAddress(const string & ip, unsigned short port);
    inetAddress(struct sockaddr_in addr);
    struct sockaddr_in * getAddressPtr();
    string ip()const;
    unsigned short port()const;
    void debug();
};

#endif
