#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shoudsave=0 ;
int count1=0,count2=0,mark=0,mark1=0 ;
/*定义存储火车信息的结构体*/
struct train 
{
    char num[10];/*列车号*/
    char city[10];/*目的城市*/
    char takeoffTime[10];/*发车时间*/
    char receiveTime[10];/*到达时间*/
    int  price;/*票价*/
    int  bookNum ;/*票数*/
};
/*订票人的信息*/
struct man 
{
    char num[10];/*ID*/
    char name[10];/*姓名*/
    int  bookNum ;/*需求的票数*/
};
/*定义火车信息链表的结点结构*/
typedef struct node 
{
    struct train data ;
    struct node * next ;
}Node,*Link ;
/*定义订票人链表的结点结构*/
typedef struct people 
{
    struct man data ;
    struct people*next ;
}bookMan,*bookManLink ;
/* 初始界面*/
void printInterface()
{
    puts("********************************************************");
    puts("*      Welcome to use the system of booking tickets    *");
    puts("********************************************************");
    puts("*     You can choose the operation:                    *");
    puts("*       1:Insert a train information                   *");
    puts("*       2:Inquire a train information                  *");
    puts("*       3:Book a train ticket                          *");
    puts("*       4:Update the train information                 *");
    puts("*       5:Advice to you about the train                *");
    puts("*       6:save information to file                     *");
    puts("*       7:quit the system                              *");
    puts("********************************************************");
}
/*添加一个火车信息*/
void InsertTraininfo(Link linkhead)
{
    struct node *p,*r,*s ;
    char num[10];
    r = linkhead ;
    s = linkhead->next ;
    while(r->next!=NULL)
    r=r->next ;
    while(1)
    {
        printf("please input the number of the train(0-return)");
        scanf("%s",num);
        if(strcmp(num,"0")==0)
          break ;
        /*判断是否已经存在*/
        while(s)
        {
            if(strcmp(s->data.num,num)==0)
            {
                printf("the train '%s'has been born!\n",num);
                return ;
            }
            s = s->next ;
        }
        p = (struct node*)malloc(sizeof(struct node));
        strcpy(p->data.num,num);
        printf("Input the city where the train will reach:");
        scanf("%s",p->data.city);
        printf("Input the time which the train take off:");
        scanf("%s",p->data.takeoffTime);
        printf("Input the time which the train receive:");
        scanf("%s",&p->data.receiveTime);
        printf("Input the price of ticket:");
        scanf("%d",&p->data.price);
        printf("Input the number of booked tickets:");
        scanf("%d",&p->data.bookNum);
        p->next=NULL ;
        r->next=p ;
        r=p ;
        shoudsave = 1 ;
    }
}
/*打印火车票信息*/
void printTrainInfo(struct node*p)
{
    puts("\nThe following is the record you want:");
    printf(">>number of train: %s\n",p->data.num);
    printf(">>city the train will reach: %s\n",p->data.city);
    printf(">>the time the train take off: %s\nthe time the train reach:  %s\n",p->data.takeoffTime,p->data.receiveTime);
    printf(">>the price of the ticket:  %d\n",p->data.price);
    printf(">>the number of  booked tickets: %d\n",p->data.bookNum);
}

struct node * Locate1(Link l,char findmess[],char numorcity[])
{
    Node*r ;
    if(strcmp(numorcity,"num")==0)
    {
        r=l->next ;
        while(r)
        {
            if(strcmp(r->data.num,findmess)==0)
            return r ;
            r=r->next ;
        }
    }
    else if(strcmp(numorcity,"city")==0)
    {
        r=l->next ;
        while(r)
        {
            if(strcmp(r->data.city,findmess)==0)
            return r ;
            r=r->next ;
        }
    }
    return 0 ;
}

/*查询火车信息*/
void QueryTrain(Link l)

{
    Node *p ;
    int sel ;
    char str1[5],str2[10];
    if(!l->next)
    {
        printf("There is not any record !");
        return ;
    }
    printf("Choose the way:\n>>1:according to the number of train;\n>>2:according to the city:\n");
    scanf("%d",&sel);
    if(sel==1)
    {
        printf("Input the the number of train:");
        scanf("%s",str1);
        p=Locate1(l,str1,"num");
        if(p)
        {
            printTrainInfo(p);
        }
        else 
        {
            mark1=1 ;
            printf("\nthe file can't be found!");
        }
    }
    else if(sel==2)
    {
        printf("Input the city:");
        scanf("%s",str2);
        p=Locate1(l,str2,"city");
        if(p)
        {
            printTrainInfo(p);
        }
        else 
        {
            mark1=1 ;
            printf("\nthe file can't be found!");
        }
    }
}

/*订票子模块*/
void BookTicket(Link l,bookManLink k)
{
    Node*r[10],*p ;
    char ch,dem ;
    bookMan*v,*h ;
    int i=0,t=0 ;
    char str[10],str1[10],str2[10];
    v=k ;
    while(v->next!=NULL)
    v=v->next ;
    printf("Input the city you want to go: ");
    scanf("%s",&str);
    p=l->next ;
    while(p!=NULL)
    {
        if(strcmp(p->data.city,str)==0)
        {
            r[i]=p ;
            i++;
        }
        p=p->next ;
    }
    printf("\n\nthe number of record have %d\n",i);
    for(t=0;t<i;t++)
    printTrainInfo(r[t]);
    if(i==0)
    printf("\n\t\t\tSorry!Can't find the train for you!\n");
    else 
    {
        printf("\ndo you want to book it?<1/0>\n");
        scanf("%d",&ch);
        if(ch == 1)
        {
            h=(bookMan*)malloc(sizeof(bookMan));
            printf("Input your name: ");
            scanf("%s",&str1);
            strcpy(h->data.name,str1);
            printf("Input your id: ");
            scanf("%s",&str2);
            strcpy(h->data.num,str2);
            printf("Input your bookNum: ");
            scanf("%d",&dem);
            h->data.bookNum=dem ;
            h->next=NULL ;
            v->next=h ;
            v=h ;
            printf("\nLucky!you have booked a ticket!");
            getch();
            shoudsave=1 ;
        }
    }
}
bookMan*Locate2(bookManLink k,char findmess[])
{
    bookMan*r ;
    r=k->next ;
    while(r)
    {
        if(strcmp(r->data.num,findmess)==0)
         {
         mark=1 ;
         return r ;
         }
         r=r->next ;
    }
    return 0 ;
}
/*修改火车信息*/
void UpdateInfo(Link l)
{
    Node*p ;
    char findmess[20],ch ;
    if(!l->next)
    {
        printf("\nthere isn't record for you to modify!\n");
        return ;
    }
    else 
    {
        QueryTrain(l);
        if(mark1==0)
        {
            printf("\nDo you want to modify it?\n");
            getchar();
            scanf("%c",&ch);
            if(ch=='y');
            {
                printf("\nInput the number of the train:");
                scanf("%s",findmess);
                p=Locate1(l,findmess,"num");
                if(p)
                {
                    printf("Input new number of train:");
                    scanf("%s",&p->data.num);
                    printf("Input new city the train will reach:");
                    scanf("%s",&p->data.city);
                    printf("Input new time the train take off");
                    scanf("%s",&p->data.takeoffTime);
                    printf("Input new time the train reach:");
                    scanf("%s",&p->data.receiveTime);
                    printf("Input new price of the ticket::");
                    scanf("%d",&p->data.price);
                    printf("Input new number of people who have booked ticket:");
                    scanf("%d",&p->data.bookNum);
                    printf("\nmodifying record is sucessful!\n");
                    shoudsave=1 ;
                }
                else 
                printf("\t\t\tcan't find the record!");
            }
        }
        else 
         mark1=0 ;
    }
}
/*系统给用户的提示信息*/
void AdvicedTrains(Link l)
{
    Node*r ;
    char str[10];
    int mar=0 ;
    r=l->next ;
    printf("Iuput the city you want to go: ");
    scanf("%s",str);
    while(r)
    {
        if(strcmp(r->data.city,str)==0&&r->data.bookNum<200)
        {
            mar=1 ;
            printf("\nyou can select the following train!\n");
            printf("\n\nplease select the fourth operation to book the ticket!\n");
            printTrainInfo(r);
        }
        r=r->next ;
    }
    if(mar==0)
    printf("\n\t\t\tyou can't book any ticket now!\n");
    
}
/*保存火车信息*/
void SaveTrainInfo(Link l)
{
    FILE*fp ;
    Node*p ;
    int count=0,flag=1 ;
    fp=fopen("c:\\train.txt","wb");
    if(fp==NULL)
    {
        printf("the file can't be opened!");
        return ;
    }
    p=l->next ;
    while(p)
    {
        if(fwrite(p,sizeof(Node),1,fp)==1)
        {
            p=p->next ;
            count++;
        }
        else 
        {
            flag=0 ;
            break ;
        }
    }
    if(flag)
    {
        printf("the number of the record which have been saved is %d\n",count);
        shoudsave=0 ;
    }
    fclose(fp);
}
/*保存订票人的信息*/
void SaveBookmanInfo(bookManLink k)
{
    FILE*fp ;
    bookMan*p ;
    int count=0,flag=1 ;
    fp=fopen("c:\\man.txt","wb");
    if(fp==NULL)
    {
        printf("the file can't be opened!");
        return ;
    }
    p=k->next ;
    while(p)
    {
        if(fwrite(p,sizeof(bookMan),1,fp)==1)
        {
            p=p->next ;
            count++;
        }
        else 
        {
            flag=0 ;
            break ;
        }
    }
    if(flag)
    {
        printf("the number of the record which have been saved is %d\n",count);
        shoudsave=0 ;
    }
    fclose(fp);
}

int main()
{
    FILE*fp1,*fp2 ;
    Node*p,*r ;
    char ch1,ch2 ;
    Link l ;
    bookManLink k ;
    bookMan*t,*h ;
    int sel ;
    l=(Node*)malloc(sizeof(Node));
    l->next=NULL ;
    r=l ;
    k=(bookMan*)malloc(sizeof(bookMan));
    k->next=NULL ;
    h=k ;
    fp1=fopen("c:\\train.txt","ab+");
    if((fp1==NULL))
    {
        printf("can't open the file!");
        return 0 ;
    }
    while(!feof(fp1))
    {
        p=(Node*)malloc(sizeof(Node));
        if(fread(p,sizeof(Node),1,fp1)==1)
        {
            p->next=NULL ;
            r->next=p ;
            r=p ;
            count1++;
        }
    }
    fclose(fp1);
    fp2=fopen("c:\\man.txt","ab+");
    if((fp2==NULL))
    {
        printf("can't open the file!");
        return 0 ;
    }
    
    while(!feof(fp2))
    {
        t=(bookMan*)malloc(sizeof(bookMan));
        if(fread(t,sizeof(bookMan),1,fp2)==1)
        {
            t->next=NULL ;
            h->next=t ;
            h=t ;
            count2++;
        }
    }
    fclose(fp2);
    while(1)
    {
        clrscr();
        printInterface();
        printf("please choose the operation:  ");
        scanf("%d",&sel);
        clrscr();
        if(sel==8)
        {
            if(shoudsave==1)
            {
                getchar();
                printf("\nthe file have been changed!do you want to save it(y/n)?\n");
                scanf("%c",&ch1);
                if(ch1=='y'||ch1=='Y')
                {
                    SaveBookmanInfo(k);
                    SaveTrainInfo(l);
                }
            }
            printf("\nThank you!!You are welcome too\n");
            break ;
            
        }
        switch(sel)
        {
            case 1 :
              InsertTraininfo(l);break ;
            case 2 :
              QueryTrain(l);break ;
            case 3 :
              BookTicket(l,k);break ;
            case 4 :
              UpdateInfo(l);break ;
            case 5 :
              AdvicedTrains(l);break ;
            case 6 :
              SaveTrainInfo(l);SaveBookmanInfo(k);break ;
            case 7 :
            return 0;
        }
        printf("\nplease press any key to continue.......");
        getch();
    }
 return 0;
}
