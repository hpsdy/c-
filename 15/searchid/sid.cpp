#include<cstdio>
#include<iostream>
using namespace std;
int main(int argc,char *argv[]){
	uint64_t sid=0;
	cin>>sid;
	printf("%08x\n", uint32_t(sid >> 32));
        printf("%08x\n", uint32_t(sid));
	return 0;
}
