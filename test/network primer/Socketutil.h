#pragma once
#ifndef __SOCKETUTIL_H__
#define __SOCKETUTIL_H__

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/eventfd.h>
#include <sys/epoll.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>



inline int create_socket_fd()
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sfd)
    {
        perror("create sfd err");
    }
    return sfd;
}
inline void set_non_block(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fd,F_SETFL, 0);
}
inline int createEpollFd()
{
    int efd = epoll_create1(0);
    if(-1 == efd)
        perror("create epollfd err");
    return efd;
}
inline void addEpollRead(int efd, int fd)
{
    struct epoll_event evs;
    evs.data.fd = fd;
    evs.events = EPOLLIN;
    int ret = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &evs);
    if(-1 == ret){
        perror("epoll add read err");
        exit(EXIT_FAILURE);
    }
}
inline void delEpollRead(int efd, int fd)
{
    struct epoll_event evs;
    evs.data.fd = fd;
    evs.events = EPOLLIN;
    int ret = epoll_ctl(efd, EPOLL_CTL_DEL, fd, &evs);
    if(-1 == ret){
        perror("epoll del read err");
        exit(EXIT_FAILURE);
    }
}
inline int createEventFd()
{
    int evefd = eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
    if(-1 == evefd)
        perror("eventfd create err");
    return evefd;
}
inline size_t recv_peer(int fd, char * buf, int size)
{
    int nread;
    do{
        nread = ::recv(fd, buf, size, MSG_PEEK);//201707026 12:27
    }while(nread == -1 && errno == EINTR);
    return nread;
}
inline bool isConnectionclosed(int fd)
{
    char buf[1024];
    int nread = recv_peer(fd,buf,1024);
    if(nread == -1)
    {
        perror("recv_peer");
        return 1;
    }
    return 0 == nread; 
}
#endif
