#include<iostream>
#include<string>
#include<pthread.h>
#include<unistd.h>
#include<cstdio>
using namespace std;
int a=0;
void *thread_func(void * argc){
	while(1){
		//printf("%s:%d\n",(char*)argc,a);	
		++a;
		sleep(1);
	}
}
int main(){
	int i1=1;
	int i2=2;
	int i3=3;
	printf("%d:%d:%d",i1,i2,i3);
	pthread_t t1;
	pthread_create(&t1,NULL,thread_func,(void*)"one");
	pthread_create(&t1,NULL,thread_func,(void*)"two");
	sleep(100);
	return 0;	
}
