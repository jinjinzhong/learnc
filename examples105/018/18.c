#include<stdio.h>
/*ʵ�ִ�Դ�ַ���string��Ŀ���ַ���str�ĸ��ƺ���*/
char *stringcpy(char *str,const char *string)
{
	char *s=str;
	while(*string)
		*s++=*string++;
	*s='\0';
	/*����Ŀ���ַ������׵�ַ*/
	return str;
}
/*���ַ���string���ӵ��ַ���str��β��*/
char *stringcat(char *str,const char *string)
{
	char *s=str;
	/*�ҵ��ַ���str��β��*/
	while(*s)
		s++;
	while(*string)
		*s++=*string++;
	*s='\0';
	/*����Ŀ���ַ������׵�ַ*/
	return str;
}
/*
ʵ�������ַ���str��string�ıȽ�
���strС��string���ظ�ֵ��
���str����string������ֵ��
���str����string����0
*/
int stringcmp(const char *str,const char *string)
{
	while((*str)&&(*string)&&(*str==*string))
	{
		str++;
		string++;
	}
	return (int)(*str-*string);
}
int main()
{
	char s1[20];
	const char *s2="I love ";
	const char *s3="china";
  char *pc;
  int cmp;
  clrscr(); 
  puts("***********************************");
  puts("|    The program will complish:   |");
  puts("|     strcpy,strcat,strcmp        |");
  puts("***********************************");
  printf("The string s2 is:%s\n",s2);
  printf("The string s3 is:%s\n\n",s3);
  pc=stringcpy(s1,s2);
  printf("After stringcpy s2 to s1,s1 is:\n");
  puts(pc);
  pc=stringcat(s1,s3);
  printf("After stringcat s1 and s3,s1 is:\n");
  puts(pc);
  cmp=stringcmp(s2,s3);
  if(cmp==0)
  	printf("\nThe string s2 is equal to s1\n");
  else if(cmp<0)
  	printf("\nThe string s2 is smaller to s1\n");
  else
  	printf("\nThe string s2 is larger to s1\n");
  getch();
  return 0;
}