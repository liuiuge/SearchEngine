#include "Wordqueryserver.h"
#include <stdlib.h>
#include <stdio.h>
#include <functional>

Wordqueryserver::Wordqueryserver(My_conf & conf):
    _conf(conf),
    _wqo(_conf),
    _tcpsever(_conf.get_config_map()["IP"].c_str(),
              atoi(_conf.get_config_map()["Port"].c_str())),
    _tp1(4,10)
{
    _tcpsever.setConnectionCallback(std::bind(&Wordqueryserver::onConnection,this,std::placeholders::_1));
    _tcpsever.setMessageCallback(std::bind(&Wordqueryserver::onMessage,this,std::placeholders::_1));
    _tcpsever.setCloseCallback(std::bind(&Wordqueryserver::onClose,this,std::placeholders::_1));
}
void Wordqueryserver::start()
{
    	_tp1.start();
	_tcpsever.start();
}
void Wordqueryserver::onConnection(const TcpConnectionPtr & conn)
{
    printf("%s\n",conn->toString().c_str());
    conn->send("welcome to server\n");
}
void Wordqueryserver::onMessage(const TcpConnectionPtr & conn)
{
    string s = conn->receive();
    string data;
    int pos = s.find('\n');
    if(pos >= 0)
        data = s.substr(0,pos);
    else
        data = s;
    _tp1.addtask(std::bind(&Wordqueryserver::dotask,this,conn,data));
}
void Wordqueryserver::onClose(const TcpConnectionPtr & conn)
{
    printf("%s close.\n",conn->toString().c_str());
}
void Wordqueryserver::dotask(const TcpConnectionPtr & conn, const string & data)
{
	string result = _wqo.doQeury(data);
	conn->sendInLoop(result);	
}


#ifdef HELLO
class Wordqueryserver
{
    My_conf _conf;
    wordQuery _wqo;
    Tcpserver _tcpsever;
    Threadpool _tp1;
    void onConnection(const TcpConnectionPtr & conn);
    void onMessage(const TcpConnectionPtr & conn);
    void onClose(const TcpConnectionPtr & conn);
public:
    Wordqueryserver(My_conf & conf);
    void start();
};

#endif
