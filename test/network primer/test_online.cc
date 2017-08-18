

//Author:liuiuge(1220595883@qq.com

#include "Configuration.h"
#include "Acceptor.h"
#include "Epollpoller.h"
#include "Socketutil.h"
#include "stdlib.h"
#include <iostream>

void OnConnection(const TcpConnectionPtr & conn)
{
    printf(">%s connecting\n",conn->toString().c_str());
    conn->send("welcome to server");
}
void OnMessage(const TcpConnectionPtr & conn)
{
    string s = conn->receive();
    printf(">%s",s.c_str());
    conn->send(s);
}
void onClose(const TcpConnectionPtr & conn)
{
    printf(">close connection %s\n",conn->toString().c_str());
}

int main()
{
    My_conf _conf("/home/lagrange/201707/rsssearch/test1/conf/myconf.cfg");
    map<string,string> temp = _conf.get_config_map();
    inetAddress addr(temp["IP"],(unsigned short)atoi(temp["Port"].c_str()));
//    addr.debug();
    acceptor acc(create_socket_fd(),addr);
    acc.ready();
    epollPoller poller(acc);
    poller.setConnectionCb(&OnConnection);
    poller.setMessageCb(&OnMessage);
    poller.setCloseCb(&onClose);
    poller.loop();
    return 0;
}
