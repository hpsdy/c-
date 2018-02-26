#include"head.h"
int main(){
	//int a = 10;
	const int a = 10;
	const int &c = a;
	cout<<"a:"<<a<<" "<<&a<<endl;
	cout<<"c:"<<c<<" "<<&c<<endl;
	int *b = const_cast<int *>(&c);
	*b=99;
	cout<<"a:"<<a<<" "<<&a<<endl;
	cout<<"b:"<<*b<<" "<<b<<endl;
	cout<<"c:"<<c<<" "<<&c<<endl;
	cout<<"===分割线==="<<endl;
	//int d = 10;
	const int d = 10;
	const int &e = d;
	cout<<"d:"<<d<<" "<<&d<<endl;
	cout<<"e:"<<e<<" "<<&e<<endl;
	int &f = const_cast<int &>(e);
	f=99;
	cout<<"d:"<<d<<" "<<&d<<endl;
	cout<<"e:"<<e<<" "<<&e<<endl;
	cout<<"f:"<<f<<" "<<&f<<endl;

	return 0;
}
