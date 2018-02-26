#include"head.h"
void print(int a,int b){
	cout<<a<<'\t'<<b<<endl;
}
int main(){
	int n = 10;
	print(n,n);
	n = 10;
	print(n,n++);
	n = 10;
	print(n++,n);
	n = 10;
	print(n++,n++);
	n = 10;
	print(++n,n);
	n = 10;
	print(n,++n);
	n = 10;
	print(++n,++n);
	return 0;
}
