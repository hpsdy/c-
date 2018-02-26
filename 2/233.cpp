#include<iostream>
#include<typeinfo>
using namespace std;
int main(){
	typedef double cnm;
	cnm a = 123;
	cout<<typeid(a).name()<<endl;
	const int i = 42;
	auto j = i;
	const auto &k = i;
	auto *p = &i;
	const auto j2 = i,&k2=i;
	cout<<"i"<<"整形常量:"<<typeid(i).name()<<endl;
	cout<<"j"<<"整形:"<<typeid(j).name()<<endl;
	cout<<"k"<<"整形常量引用:"<<typeid(k).name()<<endl;
	cout<<"p"<<"指向整形常量的指针:"<<typeid(p).name()<<endl;
	cout<<"j2"<<"整形常量:"<<typeid(j2).name()<<endl;
	cout<<"k2"<<"整形常量引用:"<<typeid(k2).name()<<endl;
	return 0;
}
