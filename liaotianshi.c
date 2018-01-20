#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<syslog.h>
#include<string.h>
#include<sys/socket.h>
#include<errno.h>
#include<netinet/in.h>

#define buffersize 1024

int main()
{
	//�����������̣�һ���Ƿ�����Ϣ���̣�һ���ǽ�����Ϣ����
	pid_t caller;
	pid_t recevier;

	/* ����socket���� */

	//����socket��Ϣ
	struct sockaddr_in client_sock;
	struct sockaddr_in server_sock;
	

	char buffer[buffersize];
	int socketfd;
	

	//��ʼ����,AF_UNSPEC����֧��ipv4Ҳ֧��ipv6
	if ((socketfd = socket(AF_UNSPEC, SOCK_STREAM, 0)) == -1)
	{
		perror("Establish failed");
		exit(1);
	}
	
	
	server_sock.sa_family= AF_UNSPEC;
	server_sock.sin_port = htons(22);
	server_sock.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_sock.sin_zero), 8);

	int i = 1;
	setsocketopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));

	//��socket`
	if (bind(socketfd, (struct sockaddr_in *) &server_sock, sizeof(struct sockaddr_in)) == -1)
	{
		perror("Bind fail...");
		exit(-1);
	}

	//����
	if (listen(socketfd,MAX_QUE_CONN_NM) == -1)
	{
		perror("Listen fail...");
		exit(-1);
	}
	printf("listen....");


	//��������������
	if (accept(socketfd, (struct sockaddr_in *)&client_sock, &sin_size) == -1)
	{
		perror("no accept...");
		exit(-1);
	}

    //������Ϣ
	if (recvfrom(socketfd, buffer, buffersize, 0) == -1)
	{
		perror("receive fail...");
		exit(-1);
	}
	printf("receive information: %s",buffer);

	//�ر�����
	close(socketfd);
	exit(0);

}