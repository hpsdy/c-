#include "head.h"
int main(){
	int w = '\0';
	int x=10,y=20;
	int init;
	cin>>init;
	init>100?++x,++y:--x,++y;
	cout<<"x:"<<x<<endl;
	cout<<"y:"<<y<<endl;
	cout<<"w:"<<w<<endl;
	string a1 = {'a','b','c','\0'};
	string a = "abc";
	cout<<"a:"<<a.size()<<"a1:"<<a1.size()<<endl;
	for(auto ca:a){
		cout<<ca<<endl;
	}
	cout<<"a:"<<a<<endl;
	const char *b = a.c_str();
	cout<<"b2:"<<b[2]<<endl;
	cout<<"b3:"<<b[3]<<endl;
	return 0;
}
