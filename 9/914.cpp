#include"head.h"
#include<list>
#include<array>
int main(){
	char arr[] = "abcdef";
	list<char *> olist{arr};
	vector<string> vstr(olist.begin(),olist.end());
	vstr.assign(olist.begin(),olist.end());
	for(const auto &c:vstr){
		cout<<c<<endl;
	}
	array<int,10> xa1{10,20,30};
	array<int,10> xa2{10,20,30};
	swap(xa1,xa2);
	for(auto &c:xa1){
		cout<<c<<endl;
	}
	cout<<unitbuf;
	cout<<typeid(vstr.max_size()).name()<<'\t';
	cout<<xa1.max_size()<<endl;
	return 0;
}
