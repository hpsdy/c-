#include<memory>
#include<string>
#include<iostream>
using namespace std;
void process(shared_ptr<string> p){
	cout<<*p<<endl;
}
class test{
	public:
		test(){cout<<"construct"<<endl;}
		~test(){cout<<"destruct"<<endl;}
};
int main(int argc,char **args){
	int *i = new int(100);
	delete i;
	cout<<i<<endl;
	cout<<*i<<endl;
	shared_ptr<string> p = make_shared<string>("给你我的喜与悲");
	process(p);
	cout<<p<<endl;
	cout<<*p<<endl;
	cout<<(*p).size()<<endl;
			
	process(shared_ptr<string>(new string("hello")));
	shared_ptr<test> w = make_shared<test>();
	cout<<1<<endl;
	shared_ptr<test> w1 = w; 
	cout<<2<<endl;
	shared_ptr<test> w2 = w; 
	cout<<3<<endl;
	w1.reset();
	w2.reset();
	w.reset();

	return 0;
}
