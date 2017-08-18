#include "TcpConnection.h"
#include "Epollpoller.h"
#include <string.h>
#include <iostream>
#include <sstream>
using std::string;
TcpConnection::TcpConnection(int sockfd, epollPoller *loop):
    _sockfd(sockfd),
    _sockio(sockfd),
    _localaddr(_sockfd.getlocaladdress(sockfd)),
    _peeraddr(_sockfd.getpeeraddress(sockfd)),
    _isShutdownWrite(0),
    _loop(loop)
{
    _sockfd.nonblock();
}
TcpConnection::~TcpConnection()
{
    if(!_isShutdownWrite)
    {
	_isShutdownWrite = 1;
	shutdown();
    }
    std::cout<<"~TcpConnection\n";
}
string TcpConnection::receive()
{
    char buf[65535];
    memset(buf, 0, sizeof(buf));
    size_t ret = _sockio.readline(buf, sizeof(buf));
    if(ret == 0){
        return std::string();
    }else
        return std::string(buf);
}
void TcpConnection::send(const string & msg)
{
    int len = msg.size();
    int nwrite = _sockio.writen(msg.c_str(),len);
    if(nwrite != len)
        exit(EXIT_FAILURE);
    return;
}
void TcpConnection::sendAndClose(const string & msg)
{
    send(msg);
    shutdown();
}
void TcpConnection::sendInLoop(const string & msg)
{
    _loop->runinloop(std::bind(&TcpConnection::sendAndClose,this,msg));
}
void TcpConnection::shutdown()
{
    if(!_isShutdownWrite)
        _sockfd.shutdownWrite();
    _isShutdownWrite = 1;
}
string TcpConnection::toString()
{
    std::ostringstream oss1;
    oss1<<_localaddr.ip()<<":"<<_localaddr.port()
        <<"---->"<<_peeraddr.ip()<<":"<<_peeraddr.port()<<"\n";
    return oss1.str();
}
void TcpConnection::SetConnectionCb(TcpConnectionCallback cb)
{
    _onConnectionCb = cb;
}
void TcpConnection::SetMessageCb( TcpConnectionCallback cb )
{
    _onMessageCb = cb;
}
void TcpConnection::SetCloseCb( TcpConnectionCallback cb )
{
    _onCloseCb = cb;
}
void TcpConnection::handleConnectionCb()
{
    if(_onConnectionCb)
        _onConnectionCb(shared_from_this());
}
void TcpConnection::handleMessageCb()
{
    if(_onMessageCb)
        _onMessageCb(shared_from_this());
}
void TcpConnection::handleCloseCb()
{
    if(_onCloseCb)
        _onCloseCb(shared_from_this());
}
#ifdef HELLO
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
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
#endif
