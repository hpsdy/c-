#include<iostream>
#include<string>
#include<pthread.h>
#include<unistd.h>
#include<cstdio>
#include<vector>
using namespace std;
int a=0;
void print(){
	++a;
	++a;
	++a;
	++a;
}
int main(){
	vector<int> inta{1,2,3};	
	int ab[] = {1,2,3,4};
	printf("%d:%d:%d",ab[0],ab[1],ab[2]);
	print();
	int i1=1;
	int i2=2;
	int i3=3;
	int i4=4;
	int i5=5;
	int i6=6;
	print();
	printf("%d:%d:%d",i1,i2,i3);
	return 0;	
}
