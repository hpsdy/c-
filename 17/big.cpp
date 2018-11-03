#include<iostream>
#include<cstdio>
#include<cstring>
int main(){
	int a = 0x123456;
	char b = static_cast<char>(a);
	if (b==0x12){
		std::cout<<"big"<<std::endl;
	}else{
		std::cout<<"lit"<<std::endl;
	}
	int *c = &a;
	//char *d = reinterpret_cast<char *>(c);
	char *d = (char *)(c);
	printf("size:%d\n",strlen(d));	
	printf("%c:%c:%c:%c:%c:%c\n",d[0],d[1],d[2],d[3],d[4]);
	printf("%u:%u:%u:%u:%u:%u\n",d[0],d[1],d[2],d[3],d[4]);
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",d[0],d[1],d[2],d[3],d[4]);
	printf("%d\n",*c);
	return 0;

}
