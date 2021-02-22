#include <stdio.h>


extern int open_your_eyes(void* p, int x);
extern void crash_handler_init(void);


int main(void)
{
	crash_handler_init();
	
	printf("Hello Crash Test\n");


	int n = 10;
	int a = open_your_eyes(&n, 10);
	printf("a result: %d\n", a);
	int b = open_your_eyes(NULL, 10);
	printf("b result: %d\n");

	
	return 0;
}

