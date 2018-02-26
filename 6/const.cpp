#include"head.h"
#define xxx 999
int main(){
	int a=10;
	const int &e = a;
	const int b=99;
	const int &c = b;
	int d = c;
	a = 100999;
	cout<<a<<endl;
	cout<<e<<endl;
	d=999;
	cout<<a<<endl;
	cout<<b<<endl;
	cout<<c<<endl;
	cout<<d<<endl;
	cout<<xxxyyy<<endl;
	cout<<xxx<<endl;
	return 0;

}
