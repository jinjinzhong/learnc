#include<stdio.h>
#include<stdlib.h>
#include<mcheck.h>
int main()
{
	char *mempointer;
	char buffer[] = "This is a test of the  mtrace function";
	/���ú���mtrace����¼�ڴ�й¶�����**/
	mtrace();
	//setenv("MALLOC_TRACE", "output.log", 1);
	if((mempointer=(char *)malloc(1024*sizeof(char)))==NULL)
	{
		printf("Memoryallocaton Error!\n");
		exit(0);
	}
	memcpy(mempointer,buffer,sizeof(buffer));
	return 0;
}
