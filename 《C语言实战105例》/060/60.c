#include "stdio.h" 
#include "string.h" 
int Fmod(int x,int r,int p);
int IptoInt(char *ip);
int e,d=1,n; 
int main(int argc,char *argv[]) 
{ 
	int ip,fai,p=43,q=59,ch1,i=0,j=0,edch,dech=0; 
	char *num,*cha,ch,*file={"index.html"}; 
	FILE *fp,*fp2; 
	if (argc!=3) 
	{ 
		printf("paramater error!"); 
		exit(0); 
	} 
	file=argv[2]; 
	e=IptoInt(argv[2]); 
	if ((fp2=fopen("encode.txt","w+"))==NULL) 
	{ 
		printf("can't open file \n"); 
		exit(0); 
	}  
	n=p*q;
	fai=(p-1)*(q-1); 
	if((fp=fopen(file,"r"))==NULL) 
	{ 
		printf("can't open the file %s\n",file); 
		exit(0); 
	} 
	while((ch1=fgetc(fp))!=EOF) 
	{ 
		edch=Fmod(ch1,e,n); 
		if (edch>0 && edch<10) 
		{
			fprintf(fp2,"%s","000"); 
			fprintf(fp2,"%d",edch); 
		}
		else if (edch<100 && edch>10) 
		{
			fprintf(fp2,"%s","00"); 
			fprintf(fp2,"%d",edch);
		}
		else if (edch<1000 && edch>100) 
		{
			fprintf(fp2,"%s","0"); fprintf(fp2,"%d",edch);  
		}
		else if (edch<10000 && edch>1000)
		{  
			fprintf(fp2,"%d",edch); 
		}
		else 
			fputc('\n',fp2); 
	} 
	fputc('\n',fp2); 
	printf("Encoded the file %s successfully!!\n\n",file);
	fclose(fp); 
	fclose(fp2);
	return 0;
} 
int IptoInt(char *ip) 
{ 
	int i,ei=0,len; 
	int prime=0; 
	len=strlen(ip); 
	len=strlen(ip); 
	for(i=0;i<len;i++) 
	{ 
		if(ip[i]>'0' && ip[i]<'9') 
		ei=ei+i*((int)ip[i]); 
	} 
	ei=ei/1000+(ei/100)%10+(ei/10)%10+ei%10; 
	while (((ei % 2)== 0) || ((ei % 3) == 0)) 
	{ 
		ei=ei+1;  
		if((ei%i)==0) 
		{ 
			ei--; 
			prime=0; 
			break; 
		}
	}
	return(ei); 
} 
int Fmod(int x,int r,int p) 
{
	int a,b,c=1; 
	a=x;
	b=r; 
	while (b!=0) 
	{ 
		while ((b%2)==0) 
		{ 
			b=b/2;
			a=(a*a)%p; 
		} 
		b=b-1;
		c=(a*c)%p; 
	} 
	return c; 
}
