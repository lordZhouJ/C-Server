#ifndef _COORDIN_H
#define _COORDIN_H

/*serve_tcp.c*/
  #include<stdio.h>
  #include<sys/socket.h>
  #include<netinet/in.h>
  #include<stdlib.h>
  #include<arpa/inet.h>
  #include<unistd.h>
  #include<string.h>
  #include<iostream>
  #include <thread>

/*
#ifdef __cplusplus
 
extern "C"{

#endif
    void   dealThreadServerThings()
    {

        return ;
    }
 
#ifdef __cplusplus
 
};
 
#endif
*/

class ServerTcp
{
    public:
 
	ServerTcp();

    public:
	static ServerTcp *m_instance;
	
	
	void threadMainOfServer();

	void ServerMainFunc(int serv_sock);


};

#endif
