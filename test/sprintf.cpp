#include<iostream>
#include<sstream>
using namespace std;
int main(){
	stringstream ss;
	ss<<printf("abc%sbc","qinhan");
	ss<<printf("abc%sbc","qinhan");
	ss<<printf("abc%sbc","qinhan");
	//cout<<ss.str()<<endl;
	string a,b;
	int c;
	cout<<endl;
	cout<<"======="<<endl;
	scanf("%s,%d,%s",&a,&b,&c);
	cout<<a<<endl;
	cout<<b<<endl;
	cout<<c<<endl;
	return 0;
}
