//#include"head.h"
#include<iostream>
using namespace std;
int main(){
	string a="12345a321";
	size_t c=0;
	int b = stoi(a,&c,10);
	cout<<b<<endl;
	cout<<c<<endl;
	//cout<<*c<<endl;
	return 0;
}
