#include"head.h"
int main(){
	const char *p = "abcd";
	cout<<p<<endl;
	string str="abc";
	string str1="ab";
	cout<<equal(str.begin(),str.end(),str1.begin())<<endl;
	auto c = strdup(str.c_str());
	cout<<"c:"<<*c<<endl;
	cout<<typeid(c).name()<<":"<<c<<endl;
	return 0;

}
