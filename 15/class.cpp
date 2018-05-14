#include <iostream>
using namespace std;
class test{
	public:
	test(){
		cout<<"helloworld"<<endl;
		p1();
		p1(10);
	}
	test(const char * str){
		cout<<"test char construct:"<<str<<endl;
	}

	virtual void p1(){
		cout<<"p1 pub"<<endl;
	}
	void p1(int n){
		cout<<"p1 pri:"<<n<<endl;
	}
	protected:
	int num = 999;
};
class t1:public test{
	public:
	t1()=default;
	t1(const char * str){
		cout<<"t1 construct:"<<str<<endl;
	}
	void p1(){
		cout<<"son p1 pub"<<endl;
	}
	void p2(int n){
		cout<<"son p2 pri:"<<n<<endl;
	}
	virtual int p2(char n){
		cout<<"int son p2 pri:"<<n<<endl;
		return 10;
	}


	//using test::num;
};
class t2:public t1{
	public:
	using t1::t1;
	t2(const t2 &p){
		
	}
	void p1(){
		cout<<"son p1 pub"<<endl;
	}
	using test::num;
};

int main(){
	t1 x;
	x.p1();
	x.p2(10);
	x.p2('a');
	cout<<"=========="<<endl;
	t2 y("nihaode");
	cout<<y.num<<endl;
	return 0;
}
