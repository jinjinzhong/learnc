#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <error.h>
#define BUFFERSIZE 1024
int main()
{
	int fd[2];
	int pid;
	char data[] = "abcdefg";
	int writenum;
	char buffer[BUFFERSIZE];
	int readnum;
	if (pipe(fd) < 0) 
	{ 
		perror("pipe error"); 
		exit(-1); 
	}
	switch(pid = fork())
	{
		case -1:
		  printf("creat child process error!\n");
		  return -1;
		  break;
		case 0:
			close(fd[0]);
			printf("CHILD PROCESS:\n");
			printf("The child process will send %s\n",data);
			printf("............\n");
			writenum = write(fd[1],data,sizeof(data));
			printf("Send successfully:%d bytes!\n",writenum);
			break;
		default:
			close(fd[1]);
			printf("\nPARENT PROCESS:\n");
			printf("Waiting to receive..... ");
			readnum = read(fd[0],buffer,BUFFERSIZE);
			printf("Received %d bytes\n\n",readnum);
			break;
	}
	return 0;
}
