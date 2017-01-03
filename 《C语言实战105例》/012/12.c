#include <stdio.h>
char token;

/*�������Ҫʹ�õ���һЩ����*/
void match( char expectedToken ) /*�Ե�ǰ�ı�־����ƥ��*/
{
	if( token == expectedToken ) token = getchar(); /*ƥ��ɹ�����ȡ��һ����־*/
	else 
	{       
		printf("cannot match\n");
		exit(1); /*ƥ�䲻�ɹ����˳�����*/
	}
}

int low( void )/*���ڼ�����ʽ�м�����͵�����*/
{
	int result = mid(); /*����ȼӼ��������ȼ���ߵĲ���*/
	while(( token == '+' ) || ( token == '-' ))
		if ( token == '+')
		{
			match('+');     /*���мӷ�����*/
			result += mid();
			break;
		}
		else if ( token == '-')
		{
			match('-');    /*���м�������*/
			result -= mid(); 
			break;
		}
	return result;
}

int mid( void )/*���ڼ�����ʽ�м���ϸߵ�����*/
{
	int div; /*����*/
	int result = high();   /*����ȳ˳��������ȼ���ߵĲ���*/
	while(( token == '*' ) || ( token == '/' ))
		if ( token == '*')
		{
			match('*');  /*���г˷�����*/
			result *= high();
			break;    
		}
		else if (token == '/')
		{
			match('/');   /*���г�������*/
			div = high();
			if( div == 0 ) /*��Ҫ�жϳ����Ƿ�Ϊ0*/
			{
				printf( "����Ϊ0.\n" );
			  	exit(1);
			}
			result /= div; 
			break;
		}
	return result;
}

int high( void )/*���ڼ�����ʽ�м�����ߵ����㣬��������������*/
{
	int result; 
	if( token == '(' ) /*�������ŵ�����*/
	{
		match( '(' );
		result = low();/*�ݹ������ʽ*/
		match(')');
	}
	else if ( token>= '0'&&token<='9' ) /*ʵ�ʵ�����*/
	{
		ungetc( token, stdin ); /*��������ַ��˻�����������Ϊ��ȡ������*/
		scanf( "%d", &result ); /*��������*/
		token = getchar();  /*������ǰ�ı�־*/
	}
	else
	{
		 printf("The input has unexpected char\n"); /*��������Ҳ��������*/
		 exit(1);
	}
	return result;
}


main()
{   
	int result;  /*����Ľ��*/                   
	printf("*****************************************\n");
	printf("**Welcome to use this simple calculator**\n"); 
	printf("**Please input a multinomial like      **\n");
	printf("**                    6-3*(5-1)/2+14/7 **\n");
	printf("*****************************************\n");
	token = getchar(); /*�����һ������*/
	
	result = low(); /*���м���*/
	if( token == '\n' ) /* �Ƿ�һ�н��� */
		printf( "The answer is : %d\n", result );
	else 
	{
		printf( "Unexpected char!");
		exit(1); /* ������������ַ� */
	}
	scanf("%d",result);
	return 0;
}

