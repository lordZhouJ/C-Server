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

#include "server_tcp.h"

using namespace std;
 #ifdef __cplusplus
 
 extern "C"{
 
 #endif
     void   dealThreadServerThings()
     {
	ServerTcp *p = new ServerTcp();
	p->threadMainOfServer();
        
	return ;
     }
 
 #ifdef __cplusplus
 
 };
 
 #endif

int main(){


    //实例化从c++的类
   // ServerTcp *p = new ServerTcp;

    thread mythread1(dealThreadServerThings);
    mythread1.join();
    //mythread1.detach();
    cout << "主线程执行" << endl;
    return 0;
}

