#include<stdio.h>
#include<stdlib.h>
#define BUFFERSIZE 1024  /*������������1024���ַ�*/
int main()
{
	int a,b,sum;         /*��������������ֱ�洢�ڱ���a��b�У�sum=a+b*/
	char buffer[BUFFERSIZE];
	printf("***********************************\n");
	printf("*  Welcome to use our counter     *\n");
	printf("*  Input two integers in one line *\n");
	printf("*  The sum will be printed        *\n");
	printf("*  Input the char '#' to quit     *\n");
	printf("***********************************\n");
	/*�ӱ�׼���루stdin����ȡ��������ݣ��洢��buffer��.
	�����ȡ�ĵ�һ���ַ���'#'���Ƴ�����*/
	while((fgets(buffer,BUFFERSIZE,stdin)!=NULL)&&(buffer[0]!='#'))
	{
		if(sscanf(buffer,"%d %d",&a,&b)!=2)              /*����洢��buffer�е�һ������*/
			{
				printf("The input is skipped:%s",buffer);/*�����������ֲ��������򱨴�*/
				continue;                               /*������ȡ��һ������*/			
			}
		sum=a+b;                                         /*����a��b�ĺ�*/
		printf("The sum of %d and %d is %d\n",a,b,sum);  /*���������*/
	}
	return 0;
}
