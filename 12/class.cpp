#include<iostream>
#include<memory>
#include<string>
using namespace std;
class test1{
	public:
	test1(){cout<<"construct1"<<endl;}
	~test1(){cout<<"destory1"<<endl;}
};
class test2{
	public:
	test2(){cout<<"construct2"<<endl;}
	~test2(){cout<<"destory2"<<endl;}
};
class test:public test2,public test1{
	public:
	test(){cout<<"construct"<<endl;}
	~test(){cout<<"destory"<<endl;}
};
class xy{
	public:
		xy(int p);
	private:
		int num;
};
xy::xy(int p):num(p){
	cout<<num<<endl;
}

int main(){
	allocator<test> a;
	test *p = a.allocate(3);
	a.construct(p);
	a.destroy(p);
	a.deallocate(p,3);
	xy ww(100);
	return 0;
}
