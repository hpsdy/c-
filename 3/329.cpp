#include<iostream>
#include<string>
#include<cstring>
#include<vector>

using namespace std;
int main(){
	int a[2] = {1,2};
	char b[] = {'a','b','c','\0'};
	char *c = "abc";
	char d[] = "abc";
	cout<<b<<"\t"<<c<<"\t"<<d<<endl;
	cout<<sizeof(b)<<endl;
	cout<<sizeof(b[0])<<endl;
	cout<<sizeof(c)<<endl;
	cout<<sizeof(c[0])<<endl;
	cout<<sizeof(d)<<endl;
	cout<<sizeof(d[0])<<endl;

	return 0;
}
