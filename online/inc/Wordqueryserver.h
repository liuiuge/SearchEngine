#pragma once
#ifndef __WORDQUERYSERVER_H__
#define __WORDQUERYSERVER_H__
#include "Configuration.h"
#include "Wordquery.h"
#include "Tcpserver.h"
#include "Threadpool.h"
class Wordqueryserver
{
    My_conf _conf;
    wordQuery _wqo;
    Tcpserver _tcpsever;
    Threadpool _tp1;
    void onConnection(const TcpConnectionPtr & conn);
    void onMessage(const TcpConnectionPtr & conn);
    void onClose(const TcpConnectionPtr & conn);
	void dotask(const TcpConnectionPtr & conn, const string & msg);
public:
    Wordqueryserver(My_conf & conf);
    void start();
};

#endif
