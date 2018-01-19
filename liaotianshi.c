#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<syslog.h>
#include<string>
#include<sys/socket.h>
#include<errno.h>

int main()
{
	//定义两个进程，一个是发送信息进程，一个是接收信息进程
	pid_t caller;
	pid_t recevier;

	/* 建立socket连接 */

	//保存socket信息
	struct sockaddr_in client_sock;
	struct sockaddr_in server_sock;
	
	string information;
	int socketfd;
	

	//开始建立
	if ((socketfd = socket(AF_UNSPEC, SOCK_STREAM, 0)) == -1)
	{
		perror("Establish failed");
		exit(1);
	}
	
	
	server_sock.sa_family= AF_UNSPEC;
	server_sock.sin_port = htons(22);
	server_sock.sin_addr.s_addr = INADDR_ANY;
	bzeros(&(server_sock.sin_zero), 8);


}