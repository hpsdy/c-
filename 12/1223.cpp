#include<iostream>
#include<cstring>
using namespace std;
int main(){
	const char *one = "hello ";
	const char *two = "world";
	char *p = new char[strlen(one)+strlen(two)+1];
	strcpy(p,one);
	strcat(p,two);
	cout<<p<<endl;
	string c = "hello ";
	string b = "qinhan";
	strcpy(p,(c+b).c_str());
	cout<<p<<endl;
	delete [] p;
	return 0;
}
