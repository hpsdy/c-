#include"head.h"
class test{
	public:
	test(int a,int b){
		cout<<a<<'\t'<<b<<endl;
	}

};
int main(){
	list<test> l;
	auto b = l.begin();
	l.emplace(b,10,20);
	return 0;	
}
