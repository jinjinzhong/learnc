#include<stdio.h>
#include<stdlib.h>
#define BUFFERSIZE 1024  /*���������������1024���ַ�*/
int main()
{
	unsigned short a,b,sum;         /*��������������ֱ�洢�ڱ���a��b�У�sum=a+b*/
	char buffer[BUFFERSIZE];
	printf("***********************************\n");
	printf("*  Welcome to use our counter     *\n");
	printf("*  Input two integers in one line *\n");
	printf("*  The sum will be printed        *\n");
	printf("*  Input the char '#' to quit  s  *\n");
	printf("***********************************\n");
	/*�ӱ�׼���루stdin����ȡ��������ݣ��洢��buffer��.
	�����ȡ�ĵ�һ���ַ���'#'���Ƴ�����*/
	while((fgets(buffer,BUFFERSIZE,stdin)!=NULL)&&(buffer[0]!='#'))
	{
		if(sscanf(buffer,"%hd %hd",&a,&b)!=2)            /*�����洢��buffer�е�һ������*/
			fprintf(stderr,"The input is skipped:%s",buffer);
		sum=a+b;                                       /*����a��b�ĺ�*/
		printf("The sum of %d and %d is %d\n",a,b,sum);/*���������*/
	}
	return 0;
}