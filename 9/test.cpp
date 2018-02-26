#include"head.h"
int main(){
	int c=100;
	int a=c,&b=c;
	a=9;
	cout<<a<<'\t'<<b<<'\t'<<c<<endl;
	b=8;
	cout<<a<<'\t'<<b<<'\t'<<c<<endl;
	return 0;

}
