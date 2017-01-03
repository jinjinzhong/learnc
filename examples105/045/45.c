#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFERSIZE 1024
#define MAXACCOUNT 1000
typedef struct BankAccount
{
	int account;
	int key;
	char name[32];
	float balance;
}BANKACCOUNT;

BANKACCOUNT accountCollection[MAXACCOUNT];
int curAccount = 0;


void InsertAccount(FILE *fp)
{
	BANKACCOUNT newaccount;
      	printf("please input the account information\n");
	printf(">>account num:");
	scanf("%d",&(newaccount.account));
	printf(">>key:");
	scanf("%d",&(newaccount.key));
	printf(">>name:");
	scanf("%s",newaccount.name);
	printf(">>balance:");
	scanf("%f",&(newaccount.balance));
	fseek(fp,0,SEEK_END);
	fprintf(fp,"%d %d %s %.2f\n",newaccount.account,newaccount.key,newaccount.name,newaccount.balance);
}
void GetAccount(FILE *fp)
{
	int accountnum;
	int key;
	char name[32];
	float balance;
	int i =0,j;
	char buffer[BUFFERSIZE];
	int len;
	curAccount = 0;
	fseek(fp,0,SEEK_SET);
	while(!feof(fp))
	{
		fscanf(fp,"%d %d %s %f",&accountnum,&key,name,&balance);
		accountCollection[curAccount].account = accountnum;
		accountCollection[curAccount].key = key;
		strcpy(accountCollection[curAccount].name ,name);
		accountCollection[curAccount].balance = balance;
		curAccount++;
	}
}
void ListAccount(FILE *fp)
{
	
	int i =0;
	printf("There is %d accounts at all:\n",curAccount-1);
	for(i = 0;i< curAccount-1;i++)
	{
		printf("ACCOUNT[%d]:\n",i+1);
		printf(">>accountnum:%d\n",accountCollection[i].account);
		printf(">>accountnum:%s\n",accountCollection[i].name);
		printf(">>accountnum:%.2f\n",accountCollection[i].balance);
	}
}
int SearchAccount(FILE *fp,int accountnum)
{
   	int i =0;
	for(i = 0;i< curAccount-1;i++)
	{
		if(accountCollection[i].account == accountnum)
		{
			printf("ACCOUNT[%d]:\n",i+1);
			printf(">>accountnum:%d\n",accountCollection[i].account);
			printf(">>accountnum:%s\n",accountCollection[i].name);
			printf(">>accountnum:%.2f\n",accountCollection[i].balance);
			return 1;
		}
	}
	return 0;
}
void DelAccount(FILE *fp,int accountnum)
{
	int i;
	if(SearchAccount(fp,accountnum)==0)
		printf("Can't find the account\n");
	else
	{
		for(i = 0;i<curAccount-1;i++)
		{
			if(accountCollection[i].account != accountnum)
			fprintf(fp,"%d %d %s %.2f\n",accountCollection[i].account,accountCollection[i].key,accountCollection[i].name,accountCollection[i].balance);
		}
		printf("delete successfully!\n");
	}
}
int main()
{
	FILE *fp;
	int accountnum;
	int i;
	do{
		clrscr();
		puts("********************************************");
		puts("*            You can choose :              *");
		puts("*    1 : Insert a new Account              *");
		puts("*    2 : List all  Accounts                *");
		puts("*    3 : Find a  Account                   *");
		puts("*    4 : Delete a Account                  *");
		puts("*    5 : quit                              *");
		puts("********************************************");
		puts("Please input your choice:");
		scanf("%d",&i);
		clrscr();
		switch(i)
		{
		      case 1:
			if(!(fp =  fopen("account.txt","a+")))
			{
				printf("can't open the file account.txt\n");
				exit(0);
			}
			InsertAccount( fp);
			
			printf("press any key to continue.....\n");
			getch();
			fclose(fp);
			break;
		    case 2:
			if(!(fp =  fopen("account.txt","r")))
			{
				printf("can't open the file account.txt\n");
				exit(0);
			}
			GetAccount(fp);
			ListAccount(fp);
			
			fclose(fp);
			printf("press any key to continue.....\n");
			getch();
			break;
		    case 3:
			printf("please input the account num:\n");
			scanf("%d",&accountnum);
			if(!(fp =  fopen("account.txt","r")))
			{
				printf("can't open the file account.txt\n");
				exit(0);
			}
			GetAccount(fp);
			if(!SearchAccount(fp,accountnum))
				printf("There is not the account:%d\n",accountnum);
			
			fclose(fp);
			printf("press any key to continue.....\n");
			getch();
			break;
		    case 4:
			printf("please input the account num:\n");
			scanf("%d",&accountnum);
			if(!(fp =  fopen("account.txt","r")))
			{
				printf("can't open the file account.txt\n");
				exit(0);
			}
			GetAccount(fp);
			fclose(fp);
			if(!(fp =  fopen("account.txt","w+")))
			{
				printf("can't open the file account.txt\n");
				exit(0);
			}
			DelAccount(fp,accountnum);
			fclose(fp);
			printf("press any key to continue.....\n");
			getch();
			break;
		    default: 
		        break;	
		}
	}while(i != 5);
	getch();
	return 0;
}




