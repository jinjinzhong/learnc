#include<stdio.h>
char *p[10]={"��","һ","��","��","��","��","��","��","��","��"};
void PrintInterger(char a[], int len);/*����������� */
void PrintDecimal(char a[],int len);/*���С������ */
int main(void)
{
   char Number[128];/* ��������û���������� */
   char Interger[64], Decimal[64];/* �ֱ�����������������С������ */
   int lenI,lenD;/* �ֱ��¼������С�����ֵĳ��� */
   int i,j;
   puts("*************************************");
   puts("*      This is a print program      *");
   puts("*           used in a bank          *");
   puts("*************************************");
   puts("please input the money:");
   gets(Number);
   i=0;j=0;
   /* ��������������������� */
   while((Number[i]!= '/0') && (Number[i]!= '.' )&& (Number[i] >= '0') && (Number[i] <= '9'))
   {
   	   Interger[i]=Number[i];
   	   i++;
   }
   lenI = i;
   if(Number[i]== '.')
   {
   	   i++;
   	   /*�������������С������*/
   	   while(Number[i]!= '/0' && Number[i] >= '0' && Number[i] <= '9')
   	   {
   	   	   Decimal[j++]=Number[i++];
   	   }
   	   /* ��ȷ��С�����4λ�� */
   	   if((j >= 4 )&& (Decimal[4] > '5'))
   	   {    
   	   	   Decimal[3]+=1;/* ����4��������� */
   	   	   Decimal[4] = '/0';
   	   }
   }
   if(j >= 4)
     lenD = 4;
   else
     lenD = j;
   PrintInterger(Interger, lenI);
   PrintDecimal(Decimal,lenD);
   printf("\n");
   return 0;
}
void PrintInterger(char a[], int len) 
{
   int i, j, tag1, tag2, tag3;
   tag1=(a[len-6]=='0' && a[len-7]=='0' && a[len-8]=='0');
   tag2=(a[len-14]=='0' && a[len-15]=='0' && a[len-16]=='0');
   tag3=(a[len-22]=='0' && a[len-23]=='0' && a[len-24]=='0');
   printf("����Ǯ���ǣ�\n"); 
   for(i=0,j=len; i<len && j>0; i++,j--)
   {
      if(a[i] == '0' && i != len-1)
      {
         if((j == 5 && tag1) || (j == 13 && tag2) || (j == 21 && tag3 ))
          ;  
         else if((j == 21 && ! tag3 )||(j == 5 && ! tag1)||(j == 13 && ! tag2))
          printf("��");        
         else if(j == 9 || j == 17 )
          printf("��");
       else if(a[i+1] == '0' && i != len-1)
          ;
         else if(a[i+1] != '0' && i != len-1) 
          printf("��");
         else
          ;
      }   
      else if(a[i] == '0' && i == len-1)
       ;
      else if(a[i] != '0')
      {
         /*�������������ֵ�ת��*/
         switch(a[i]) 
         {
            case '1': printf("%s",p[1]); break;
            case '2': printf("%s",p[2]); break;
            case '3': printf("%s",p[3]); break;
            case '4': printf("%s",p[4]); break;
            case '5': printf("%s",p[5]); break;
            case '6': printf("%s",p[6]); break;
            case '7': printf("%s",p[7]); break;
            case '8': printf("%s",p[8]); break;
            case '9': printf("%s",p[9]); break;
            default:  printf("error"); ; break;
         }  
         /*�����Ӧ�ĵ�λ*/
         switch(j) 
         {
            case 2:
            case 6:
            case 10: 
            case 14: 
            case 18: 
            case 22: printf("%s","ʮ");  break;
            case 3: 
            case 7:
            case 11: 
            case 15: 
            case 19: 
            case 23: printf("%s","��"); break;
            case 4: 
            case 8: 
            case 12:
            case 16:
            case 20:
            case 24: printf("%s","ǧ"); break;
            case 5:
            case 13: 
            case 21: printf("%s","��");  break;
            case 9: 
            case 17: printf("%s","��"); break;
            default:  printf("%s","");  break;
         }
      }     
    } 
    printf("%s","Բ"); 
}   

void PrintDecimal(char a[],int len)
{
   int i;
   for(i=0; i<len; i++)
   {
   	  /*�������������ֵ�ת��*/
      switch(a[i]) 
      {
         case '0': printf("%s",p[0]); break;
         case '1': printf("%s",p[1]); break;
         case '2': printf("%s",p[2]); break;
         case '3': printf("%s",p[3]); break;
         case '4': printf("%s",p[4]); break;
         case '5': printf("%s",p[5]); break;
         case '6': printf("%s",p[6]); break;
         case '7': printf("%s",p[7]); break;
         case '8': printf("%s",p[8]); break;
         case '9': printf("%s",p[9]); break;
         default:  printf("%s",p[0]); ; break;
      }
      /*�����Ӧ�ĵ�λ*/
      switch(i) 
      {
         case 0: printf("%s","��"); break;
         case 1: printf("%s","��"); break;
         case 2: printf("%s","��"); break;
         case 3: printf("%s","��"); break;
         default:; break;
      }   
   }   
}       
 
