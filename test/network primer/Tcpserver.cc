#include "Tcpserver.h"
#include "Socketutil.h"

Tcpserver::Tcpserver(unsigned short port):
    _acc(create_socket_fd(),inetAddress(port)),
    _epollfd(_acc)
{
    _acc.ready();
}
Tcpserver::Tcpserver(const char * ip, unsigned short port):
    _acc(create_socket_fd(),inetAddress(ip,port)),
    _epollfd(_acc)
{
    _acc.ready();
}
void Tcpserver::setConnectionCallback(TcpserverCallback cb)
{
    _epollfd.setConnectionCb(cb);
}
void Tcpserver::setMessageCallback(TcpserverCallback cb)
{
    _epollfd.setMessageCb(cb);
}
void Tcpserver::setCloseCallback(TcpserverCallback cb)
{
    _epollfd.setCloseCb(cb);
}
void Tcpserver::start()
{
    _epollfd.loop();
}
void Tcpserver::stop()
{
    _epollfd.unloop();
}

#ifdef HELLO
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
private:
    TcpserverCallback _onConnection;
    TcpserverCallback _onMessage;
    TcpserverCallback _onClose;
};
#endif
