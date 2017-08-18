

//Author:liuiuge(1220595883@qq.com

#include "Configuration.h"
#include "Acceptor.h"
#include "Wordqueryserver.h"
#include "Socketutil.h"
#include "stdlib.h"
#include <iostream>

int main()
{
    My_conf _conf("/home/lagrange/201707/rsssearch/test2/conf/myconf.cfg");
    map<string,string> temp = _conf.get_config_map();
    inetAddress addr(temp["IP"],(unsigned short)atoi(temp["Port"].c_str()));
//    addr.debug();
    Wordqueryserver wqs(_conf);
    wqs.start();
    return 0;
}
