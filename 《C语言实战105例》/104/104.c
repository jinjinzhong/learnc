#include <stdio.h>
#define	JUDEGNUM	3	  /* ������ */
#define NAMELEN		20	/* ��������ַ��� */
#define CODELEN		10	/* ��������ַ��� */
#define FNAMELEN	80	/* �ļ�������ַ��� */
#define BUFFSIZE	128	/* ����������ַ��� */

char judgement[JUDEGNUM][NAMELEN+1] = {"judgementA","judgementB","judgementC"};
struct AthleteScore
{
	char	name[NAMELEN+1];	/* ���� */
	char 	code[CODELEN+1];	/* ѧ�� */
	int 	score[JUDEGNUM];	/* �����и��ĳɼ� */
	int   total;					  /* �ܳɼ� */
};

struct LinkNode
{
	char	name[NAMELEN+1];	/* ���� */
	char 	code[CODELEN+1];	/* ���� */
	int 	score[JUDEGNUM];	/* �����и��ĳɼ� */
	int 	total;			      /* �ܳɼ� */
	struct	LinkNode *next;	
}*head;	/* ������ָ�� */

int total[JUDEGNUM];		/* �����и����ܳɼ� */
FILE *filepoint;				/* �ļ�ָ�� */
char filename[FNAMELEN];/* �ļ��� */

/* ��ָ���ļ�����һ����¼ */
int GetRecord(FILE *fpt,struct AthleteScore *sturecord)
{
	char buf[BUFFSIZE];
	int i;
	if(fscanf(fpt,"%s",buf)!=1)
		return 0;	/* �ļ����� */
	strncpy(sturecord->name,buf,NAMELEN);
	fscanf(fpt,"%s",buf);
	strncpy(sturecord->code,buf,CODELEN);
	for(i=0;i<JUDEGNUM;i++)
		fscanf(fpt,"%d",&sturecord->score[i]);
	for(sturecord->total=0,i=0;i<JUDEGNUM;i++)
		sturecord->total+=sturecord->score[i];
	return 1;
}
/* ��ָ���ļ�д��һ����¼ */
void PutRecord(FILE *fpt,struct AthleteScore *sturecord)
{
	int i;
	fprintf(fpt,"%s\n",sturecord->name);
	fprintf(fpt,"%s\n",sturecord->code);
	for(i=0;i<JUDEGNUM;i++)
		fprintf(fpt,"%d\n",sturecord->score[i]);
	return ;
}

/* ��ʾ�˶�Ա��¼ */
void ShowAthleteRecord(struct AthleteScore *rpt)
{
	int i;
	printf("\nName   : %s\n",rpt->name);
	printf("Code   : %s\n",rpt->code);
	printf("score  :\n");
	for(i=0;i<JUDEGNUM;i++)
		printf("       %-15s : %4d\n",judgement[i],rpt->score[i]);
	printf("Total  : %4d\n",rpt->total);
}


/* �б���ʾ�˶�Ա�ɼ� */
void Listathleteinfo(char *fname)
{
	FILE *fp;
	struct AthleteScore s;
	clrscr();
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return ;
	}
	while(GetRecord(fp,&s)!=0)
	{
		ShowAthleteRecord(&s);
	}
	fclose(fp);
	return;
}

/* �������� */
struct LinkNode *CreatLinklist(char *fname)
{
	FILE *fp;
	struct AthleteScore s;
	struct LinkNode *p,*u,*v,*h;
	int i;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return NULL;
	}
	h=NULL;
	p=(struct LinkNode *)malloc(sizeof(struct LinkNode));
	while(GetRecord(fp,(struct AthleteScore *)p)!=0)
	{
		v=h;
		while(v&&p->total<=v->total)
		{
			u=v;
			v=v->next;
		}
		if(v==h)
			h=p;
		else
			u->next=p;
		p->next=v;
		p=(struct LinkNode *)malloc(sizeof(struct LinkNode));
	}
	free(p);
	fclose(fp);
	return h;
}

/* ˳����ʾ�������Ԫ */
void OutputLinklist(struct LinkNode *h)
{
	clrscr();
	while(h!=NULL)
	{
		ShowAthleteRecord((struct AthleteScore *)h);
		printf("\n");
		while(getchar()!='\n');
		h=h->next;
	}
	return;
}
/* ���˶�Ա�������Ҽ�¼ */
int SearchbyName(char *fname, char *key)
{
	FILE *fp;
	int c;
	struct AthleteScore s;
	clrscr();
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return 0;
	}
	c=0;
	while(GetRecord(fp,&s)!=0)
	{
		if(strcmp(s.name,key)==0)
		{
			ShowAthleteRecord(&s);
			c++;
		}
	}
	fclose(fp);
	if(c==0)
		printf("The athlete %s is not in the file %s.\n",key,fname);
	return 1;
}

/* ���˶�Ա������Ҽ�¼ */
int SearchbyCode(char *fname, char *key)
{
	FILE *fp;
	int c;
	struct AthleteScore s;
	clrscr();
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("Can't open file %s.\n",fname);
		return 0;
	}
	c=0;
	while(GetRecord(fp,&s)!=0)
	{
		if(strcmp(s.code,key)==0)
		{
			ShowAthleteRecord(&s);
			c++;
			break;
		}
	}
	fclose(fp);
	if(c==0)
		printf("The athlete %s is not in the file %s.\n",key,fname);
	return 1;
}
void InsertRecord()
{
	FILE *fp;
	char c,i,j,n;
	struct AthleteScore s;
	clrscr();
	printf("Please input the athletes score record file's name: \n");
	scanf("%s",filename);
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("The file %s doesn't exit.\ndo you want to creat it? (Y/N) ",filename);
		getchar();
		c=getchar();
		if(c=='Y'||c=='y')
		{
			fp=fopen(filename,"w");
			printf("Please input the record number : ");
			scanf("%d",&n);
			for(i=0;i<n;i++)
			{
				printf("Input the athlete's name: ");
				scanf("%s",&s.name);
				printf("Input the athlete's code: ");
				scanf("%s",&s.code);
				for(j=0;j<JUDEGNUM;j++)
				{
					printf("Input the %s mark: ",judgement[j]);
					scanf("%d",&s.score[j]);
				}
				PutRecord(fp,&s);
			}
			fclose(fp);
		}
	}
	fclose(fp);
	return;
}
int main()
{
	int i,j,n;
	char c;
	char buf[BUFFSIZE];
	while(1)
	{
		clrscr();
		printf("\n-------------- Input a command -----------\n");
		printf("|  i : insert record to a file.           |\n");
		printf("|  n : search record by name.             |\n");
		printf("|  c : search record by code.             |\n");
		printf("|  l : list all the records.              |\n");
		printf("|  s : sort the records by total.         |\n");
		printf("|  q : quit.                              |\n");
		printf("------------------------------------------\n");
		printf("Please input a command:\n");
		scanf("%c",&c);		/* ����ѡ������ */
		switch(c)
		{
			case 'i': 
				InsertRecord();
				getch();
				break;
			case 'n': /* ���˶�Ա������Ѱ�Ҽ�¼ */
				printf("Please input the athlete's name:\n");	
				scanf("%s",buf);
				SearchbyName(filename,buf);
				getch();
				break;
			case 'c': /* ���˶�Ա�ĺ���Ѱ�Ҽ�¼ */
				printf("Please input the athlete's code:\n");	
				scanf("%s",buf);
				SearchbyCode(filename,buf);
				getch();
				break;
			case 'l': /* �г������˶�Ա��¼ */
				Listathleteinfo(filename);
				getch();
				break;
			case 's': /* ���ִܷӸߵ���������ʾ */
				if((head=CreatLinklist(filename))!=NULL)
					OutputLinklist(head);
				getch();
				break;
			case 'q':
				return 1;
			default: 
				break;
		}
	}
	return 1;
}
