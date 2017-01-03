#include <stdio.h>
#define MAXLEN  100
#define MAXLINE 100
char Buffer[MAXLEN],filename[128];
/*�����ַ�ָ���������洢Ҫ�༭���ı���ָ��*/
char *LinePointer[MAXLINE];
/*���ı��޸ı�־*/
int Modified=0;
/*��ǰ��������*/
int LineNum;
char *CmdPointer;/*�����������ַ�ָ��*/
void Quit()
{
	int i;
	char c;
	/* �����ı��޸�,����ʾ�û��Ƿ�Ҫ����*/
	if(Modified==1)
	{
		printf("Save or not? (y/n):");
		scanf("%c",&c);
		/* ���汻�޸Ĺ������� */
		if(c=='y'||c=='Y')
			Save(); 
	}
	/* �ͷ��ڴ� */
	for(i=0;i<LineNum;i++)
		free(LinePointer[i]);	
}
void Insert()
{
	int k,m,i;
	/* ������� */
	sscanf(CmdPointer,"%d%d",&k,&m);
	/* ���������� */	
	for(i=LineNum;i>m;i--)
		LinePointer[i+k-1]=LinePointer[i-1];
	/* ����k�����ģ������뵽ָ�����飬��д���ļ�*/
	for(i=0;i<k;i++)   
	{
		fgets(Buffer,MAXLEN,stdin);
		LinePointer[m+i]=(char *)malloc(strlen(Buffer)+1);
		strcpy(LinePointer[m+i],Buffer);
	}
	/* ���������������������ı��޸ı�־*/
	LineNum+=k;	
	Modified=1;	
}
void Delete()
{
	int i,j,m,n;
	sscanf(CmdPointer,"%d%d",&m,&n);	/* ������� */
	if(n>LineNum)
		n=LineNum;
	/* ɾ������ */		
	for(i=m;i<=n;i++)	
		free(LinePointer[i-1]);
	for(i=m,j=n+1;j<=LineNum;i++,j++)
		LinePointer[i-1]=LinePointer[j-1];
	/* ���������������������ı��޸ı�־*/
	LineNum=i-1;	
	Modified=1;
}
int Save()	/* �����ļ� */
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
/* �༭�����*/
void Edit()	
{
	int i;
	FILE *fp;
	/*�����ļ���*/
	sscanf(CmdPointer,"%s",filename);	
	/* �Զ��ķ�ʽ���ļ�*/
	if((fp=fopen(filename,"r"))==NULL) 
	{/* �粻���ڣ��򴴽��ļ� */
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
		/*����������*/
		gets(Buffer);
		/*�ӹ��հ׷�*/
		for(CmdPointer=Buffer;(*CmdPointer==' ')||(*CmdPointer=='\t');CmdPointer++);
		/*������������*/
		if(*CmdPointer=='\0') 
			continue;
		switch(*CmdPointer)
		{
			/*���ñ༭����*/
			case 'e':
				/*�ӹ��������ָ�����*/
				CmdPointer++;
				Edit();
				break;
			/*���ò��뺯��*/
			case 'i':
				CmdPointer++;
				Insert();
				break;
			/*����ɾ������*/
			case 'd':
				CmdPointer++;
				Delete();
				break;
			/*�����Ƴ�����*/
			case 'q':
				flag2=1;
				Quit();
				break;
			/*�Ƿ������*/
			default:
				flag=1;
				break;		
		}
		if(flag==1)
			continue;
		/*��ʾ����*/
		printf("The text of the file %s is:\n",filename);
		for(j=0;j<LineNum;j++)
			fputs(LinePointer[j],stdout);
		if(flag2==1)
			break;
	}
	return 0;
}

		
	
		