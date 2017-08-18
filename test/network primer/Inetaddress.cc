#include "Inetaddress.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
inetAddress::inetAddress(unsigned short port)
{
    memset(&_addr,0,sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY;
}
inetAddress::inetAddress(const string & ip, unsigned short port)
{
    memset(&_addr,0,sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}
inetAddress::inetAddress(struct sockaddr_in addr):
    _addr(addr)
{}
struct sockaddr_in * inetAddress::getAddressPtr()
{
    return &_addr;
}
string inetAddress::ip()const
{
    return string(inet_ntoa(_addr.sin_addr));
}
unsigned short inetAddress::port()const
{
    return ntohs(_addr.sin_port);
}
void inetAddress::debug()
{
    std::cout<<ip()<<"\n";
    std::cout<<port()<<"\n";
}

#ifdef HELLO
    struct sockaddr_in _addr;
public:
    inetAddress(unsigned short);
    inetAddress(const string &, unsigned short);
    inetAddress(struct sockaddr_in);
    struct sockaddr_in * getAddressPtr();
    string ip();
    unsigned short port();

#endif
