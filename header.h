#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <error.h>
#include <signal.h>
#include <sys/wait.h>
#include <assert.h>

#include <pthread.h>

#define  bool  int                  // the 3 lines is for c originally
#define  true   1
#define  false  0

#define  PORT  9003
#define  BUF_LEN  1024              // ��������С
#define  MAX_CONNECTION  6          // ���������������������������и���

#define  For(i,s,t)  for(i = (s); i != (t); ++i)



#endif // HEADER_H_INCLUDED
