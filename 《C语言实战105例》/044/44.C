#include <stdio.h>
#define MAXLEN  100
#define MAXLINE 100
char Buffer[MAXLEN],filename[128];
/*定义字符指针数组来存储要编辑的文本行指针*/
char *LinePointer[MAXLINE];
/*正文被修改标志*/
int Modified=0;
/*当前正文行数*/
int LineNum;
char *CmdPointer;/*输入命令行字符指针*/
void Quit()
{
	int i;
	char c;
	/* 如正文被修改,则提示用户是否要保存*/
	if(Modified==1)
	{
		printf("Save or not? (y/n):");
		scanf("%c",&c);
		/* 保存被修改过的正文 */
		if(c=='y'||c=='Y')
			Save(); 
	}
	/* 释放内存 */
	for(i=0;i<LineNum;i++)
		free(LinePointer[i]);	
}
void Insert()
{
	int k,m,i;
	/* 读入参数 */
	sscanf(CmdPointer,"%d%d",&k,&m);
	/* 后继行向后移 */	
	for(i=LineNum;i>m;i--)
		LinePointer[i+k-1]=LinePointer[i-1];
	/* 读入k行正文，并插入到指针数组，待写入文件*/
	for(i=0;i<k;i++)   
	{
		fgets(Buffer,MAXLEN,stdin);
		LinePointer[m+i]=(char *)malloc(strlen(Buffer)+1);
		strcpy(LinePointer[m+i],Buffer);
	}
	/* 修正正文行数及设置正文被修改标志*/
	LineNum+=k;	
	Modified=1;	
}
void Delete()
{
	int i,j,m,n;
	sscanf(CmdPointer,"%d%d",&m,&n);	/* 读入参数 */
	if(n>LineNum)
		n=LineNum;
	/* 删除正文 */		
	for(i=m;i<=n;i++)	
		free(LinePointer[i-1]);
	for(i=m,j=n+1;j<=LineNum;i++,j++)
		LinePointer[i-1]=LinePointer[j-1];
	/* 修正正文行数及设置正文被修改标志*/
	LineNum=i-1;	
	Modified=1;
}
int Save()	/* 保存文件 */
{
	int i;
	FILE *fp;
	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("Can't open the %s.\n",filename);
		return 0;
	}
	for(i=0;i<LineNum;i++)
	{
		fputs(LinePointer[i],fp);
		free(LinePointer[i]);
	}
	fclose(fp);
	return 1;
}
/* 编辑命令函数*/
void Edit()	
{
	int i;
	FILE *fp;
	/*读入文件名*/
	sscanf(CmdPointer,"%s",filename);	
	/* 以读的方式打开文件*/
	if((fp=fopen(filename,"r"))==NULL) 
	{/* 如不存在，则创建文件 */
		fp=fopen(filename,"w");	
		fclose(fp);
		fp=fopen(filename,"r");
	}
	i=0;
	while(fgets(Buffer,MAXLEN,fp)==Buffer)
	{
		LinePointer[i]=(char *)malloc(strlen(Buffer)+1);
		strcpy(LinePointer[i++],Buffer);
	}
	fclose(fp);
	LineNum=i;
}
int main()
{
	int j,flag=0,flag2=0;
	LineNum=0;
	clrscr();
	printf("*******************************\n");
	printf("|       e+filename:Edit       |\n");
	printf("|       i+k+m:Insert          |\n");
	printf("|       d+m+n :Delete         |\n");
	printf("|       q :Quit               |\n");
	printf("*******************************\n");
	while(1)
	{
		printf("Please input a command:\n");
		/*读入命令行*/
		gets(Buffer);
		/*掠过空白符*/
		for(CmdPointer=Buffer;(*CmdPointer==' ')||(*CmdPointer=='\t');CmdPointer++);
		/*空行重新输入*/
		if(*CmdPointer=='\0') 
			continue;
		switch(*CmdPointer)
		{
			/*调用编辑函数*/
			case 'e':
				/*掠过命令符，指向参数*/
				CmdPointer++;
				Edit();
				break;
			/*调用插入函数*/
			case 'i':
				CmdPointer++;
				Insert();
				break;
			/*调用删除函数*/
			case 'd':
				CmdPointer++;
				Delete();
				break;
			/*调用推出函数*/
			case 'q':
				flag2=1;
				Quit();
				break;
			/*非法命令符*/
			default:
				flag=1;
				break;		
		}
		if(flag==1)
			continue;
		/*显示正文*/
		printf("The text of the file %s is:\n",filename);
		for(j=0;j<LineNum;j++)
			fputs(LinePointer[j],stdout);
		if(flag2==1)
			break;
	}
	return 0;
}

		
	
		