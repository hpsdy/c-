#include"head.h"
int main(){
	string a="123";
	string b;
	//auto x = b.insert(b.begin(),a.begin());
	auto x = b.insert(b.begin(),a.begin(),a.begin()+1);
	cout<<*b.begin()<<endl;
	cout<<*x<<endl;
	return 0;

}
