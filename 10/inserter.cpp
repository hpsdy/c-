#include"head.h"
#include<iterator>
void print(deque<int> deq){
	for(auto &c:deq){
		cout<<c<<'\t';
	}
	cout<<endl;
}
int main(){
	string str="qinhan";
	deque<int> str1,str2,str3;
	auto i1 = front_inserter(str1);
	auto i2 = back_inserter(str2);
	auto i3 = inserter(str3,str3.begin());
	i1=10;
	i1='b';
	i1='c';
	print(str1);
	i2='a';
	i2='b';
	i2='c';
	print(str2);
	i3='a';
	i3='b';
	i3='c';
	print(str3);
	return 0;
}
