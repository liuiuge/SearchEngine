#pragma once
#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.h"
#include "Socketio.h"
#include <string>
#include <memory>
#include <functional>

class epollPoller;
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection
:public std::enable_shared_from_this<TcpConnection>
{
    Socket _sockfd;
    socketio _sockio;
    const inetAddress _localaddr;
    const inetAddress _peeraddr;
    bool _isShutdownWrite;
    epollPoller * _loop;
public:
     typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;
    TcpConnection(int sockfd, epollPoller * loop);
    ~TcpConnection();
    std::string receive();
    void send(const std::string & msg);
    void sendAndClose(const std::string & msg);
    void sendInLoop(const std::string & msg);
    void shutdown();
    std::string toString();
    void SetConnectionCb(TcpConnectionCallback cb);
    void SetMessageCb(TcpConnectionCallback cb);
    void SetCloseCb(TcpConnectionCallback cb);
    void handleConnectionCb();
    void handleMessageCb();
    void handleCloseCb();
private:
    TcpConnectionCallback _onConnectionCb;
    TcpConnectionCallback _onMessageCb;
    TcpConnectionCallback _onCloseCb;
};
#endif
