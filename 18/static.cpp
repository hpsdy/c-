#include<cstdio>
static int b = 99;
#include"static.h"
//static int b = 99;
int main(){
	printf("a:%d\n",a);
	p();
	int c = 10;
	printf("c:%d\n",c);
	{
		int c = 999;
		printf("c:%d\n",c);
	}
	printf("c:%d\n",c);
	return 0;
}
