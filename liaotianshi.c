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
#include<netdb.h>

#define buffersize 1024
#define MAX_QUE_CONN_NM 5
#define  dest_file  "information_file"

int main()
{
	//�����������̣�һ���Ƿ�����Ϣ���̣�һ��  �ǽ�����Ϣ����
	pid_t caller;
	pid_t recevier;

	/* ����socket���� */

	//����socket��Ϣ
	struct sockaddr_in client_sock;
	struct sockaddr_in server_sock;
	

	char buffer[buffersize];
	int socketfd;
	
    int sin_size;

	struct flock lock;

	//��ʼ����,AF_INET֧��ipv4
	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Establish failed");
		exit(1);
	}
	
	
	server_sock.sin_family= AF_INET	;
	server_sock.sin_port = htons(4321);
	server_sock.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_sock.sin_zero), 8);

	int i = 1;
	setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));

	//��socket
	if (bind(socketfd, (struct sockaddr *) &server_sock, sizeof(struct sockaddr)) == -1)
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
	if (accept(socketfd, (struct sockaddr *)&client_sock, &sin_size) == -1)
	{
		perror("no accept...");
		exit(-1);
	}

    //������Ϣ
	if (recv(socketfd, buffer, buffersize, 0) == -1)
	{
		perror("receive fail...");
		exit(-1);
	}
	printf("receive information: %s",buffer);


	//�ͻ���
	char hostname[25];
	struct hostent *host;


	scanf("%s",hostname);
	if (gethostbyname(hostname) == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}

	memset(buffer,0,sizeof(buffer));
	scanf("���뷢�͵���Ϣ��",&buffer);
	
	client_sock.sin_family= AF_UNSPEC;
	client_sock.sin_addr = *((struct in_addr *)host -> h_addr);
	client_sock.sin_port = htons(4322);
	bzero(&(server_sock.sin_zero),8);

	if (connect(socketfd,(struct sockaddr *)&server_sock,sizeof(struct sockaddr))==-1)
	{
		perror("connect fail");
		exit(1);
	}

	if (send(socketfd,buffer,strlen(buffer),0)==-1)
	{
		perror("send fail");
		exit(1);
	}


	//����Ϣд��dest_file�ļ�����Ϊ�����¼
	dest_file = open(dest_file,O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	
	if (dest_file < 0)
	{
		printf("open fail");
		exit(1);
	}

	write(dest_file,buffer,strlen(buffer));
	fopen(dest_file, "w", stdout);

	lock.l_len = 0;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_pid = -1;
	lock.l_type = F_WRLCK;

	fcntl(dest_file, F_GETLK, &lock);

	if (lock.l_type != F_UNLCK)
	{
		if (lock.l_type == F_WRLCK)
		{
			printf("already have write lock %d",lock.l_pid);
		}
		if (lock.l_type == F_RDLCK)
		{
			printf("already have read lock %d", lock.l_pid);
		}
	}

	lock.l_type = F_WRLCK;

	if (fcntl(dest_file, F_SETLKW, &lock) < 0)
	{
		printf("lock fail %d",lock.l_type);
		return 1;
	}

	close(dest_file);

	
	//�ر�����
	close(socketfd);
	exit(0);

}
