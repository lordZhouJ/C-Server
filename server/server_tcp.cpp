/*git使用技巧：
 *git push  是将本地代码提交到远端服务器;
 *git add .  提交代码先要做的事情。
 *
 *
 * vim 下编译命令：
 * g++  server_tcp.cpp main.cpp  -o main -lpthread
 *
 * vim 运行便以后程序的命令：
 * ./main
 *
*/

#include "server_tcp.h"
#include <stdio.h>
#include <errno.h>

#define MAX_LISTEN_NUM  2

using namespace std;

ServerTcp * ServerTcp::m_instance = NULL;

ServerTcp::ServerTcp()
{

    m_instance = this ;

}


void ServerTcp::threadMainOfServer()
{
   //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serv_sock == -1)
    {
	perror("socket");
	exit(1);
    }	
    else
    {
	cout << "socket id :"<< serv_sock << endl;
    }
   //初始化socket元素
   struct sockaddr_in serv_addr;
   memset(&serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
  // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   
   serv_addr.sin_addr.s_addr = inet_addr("192.168.40.129 ");
   
   serv_addr.sin_port = htons(1234);

    cout<<"here has  run many times"<<endl;
   //绑定文件描述符和服务器的ip和端口号
   //这里是进行了sockaddr_in和sockaddr之间的转换，因为他们大小完全一致。所以可以进行这样的转换，并且不会出什么样的问题。
   bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

   while(1)
   {
        ServerMainFunc(serv_sock);
   } 

   close(serv_sock);

    return ;

}



void ServerTcp::ServerMainFunc(int  serv_sock)
{
    //进入监听状态，等待用户发起请求
    //这里的max_listen_num,是不是接受最大数目的意思？
    if(listen(serv_sock, MAX_LISTEN_NUM) !=0)
    {
	perror("bind");

	exit(1);
    }
    else
    {
	cout<<"Listening....."<<endl;
    }


    //接受客户端请求
    //定义客户端的套接字，这里返回一个新的套接字，后面通信时，就用这个clnt_sock进行通信
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1)
    {
	perror("accept");
 
         exit(1);
    }
    else
    {
	cout<< "Server Accept......"<<endl;
    }
     //接收客户端数据，并相应
     char str[256];
     read(clnt_sock, str, sizeof(str));
     cout<<"client send:" <<str<<endl;
     strcat(str, "+ACK");
     write(clnt_sock, str, sizeof(str));
 
     //关闭套接字
    close(clnt_sock);
   
     return ;
 }

