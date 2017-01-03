#include<stdio.h>
/*实现从源字符串string到目的字符串str的复制函数*/
char *stringcpy(char *str,const char *string)
{
	char *s=str;
	while(*string)
		*s++=*string++;
	*s='\0';
	/*返回目的字符串的首地址*/
	return str;
}
/*将字符串string连接到字符串str的尾部*/
char *stringcat(char *str,const char *string)
{
	char *s=str;
	/*找到字符串str的尾部*/
	while(*s)
		s++;
	while(*string)
		*s++=*string++;
	*s='\0';
	/*返回目的字符串的首地址*/
	return str;
}
/*
实现两个字符串str和string的比较
如果str小于string返回负值，
如果str大于string返回正值，
如果str等于string返回0
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