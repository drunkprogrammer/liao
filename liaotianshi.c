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
	//�����������̣�һ���Ƿ�����Ϣ���̣�һ���ǽ�����Ϣ����
	pid_t caller;
	pid_t recevier;

	/* ����socket���� */

	//����socket��Ϣ
	struct sockaddr_in client_sock;
	struct sockaddr_in server_sock;
	
	string information;
	int socketfd;
	

	//��ʼ����
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