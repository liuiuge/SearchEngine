
#include "Socket.h"
#include "Socketutil.h"
Socket::Socket(int afd):
    _fd(afd)
{}
Socket::Socket():
    _fd(create_socket_fd())
{}
void Socket::nonblock()
{
    set_non_block(_fd);
}
void Socket::shutdownWrite()
{
    if((::shutdown(_fd,SHUT_WR)) == -1)
        perror("shutdown write error\n");
}
int Socket::fd() const
{
    return _fd;
}
inetAddress Socket::getlocaladdress(int sockfd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if(::getsockname(sockfd, (struct sockaddr *)&addr, &len) == -1)
        perror("get sockname err");
    return inetAddress(addr);
}
inetAddress Socket::getpeeraddress(int sockfd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if(::getpeername(sockfd,(struct sockaddr *)&addr, &len) == -1)
        perror("get peername err");
    return addr;
}

#ifdef HELLO
    int _fd;
public:
    Socket(int);
    Socket();
    void shutdownWrite();
    void nonblock();
#endif
