#include<iostream>
#include<string>
//#include"func_util.h"
using namespace std;
//using namespace func;
#define SPLIT "||"
int main(){
	bool xb=true;
	xb?(cout<<"true"<<endl):(cout<<"false"<<endl);

	return 0;
	/*const int num=10;
	cout<<"num*:"<<&num<<endl;
	int &a = const_cast<int &>(num);
	a=100; 
	cout<<"a*:"<<&a<<",int:"<<a<<","<<num<<endl;
	int *b = const_cast<int *>(&num);
	*b=99; 
	cout<<"b*:"<<b<<",int:"<<*b<<","<<num<<endl;

	
	cout<<"=========="<<endl;
	string str;
	getline(cin,str);
	char *p = const_cast<char*>(str.c_str());
	cout<<p<<endl;
	char *tmp;
	cout<<"=========="<<endl;
	while(tmp = split_char(p,SPLIT)){
		cout<<"p:"<<((p)?p:"nullptr")<<"***tmp:"<<tmp<<endl;
	}
	return 0;*/
}
