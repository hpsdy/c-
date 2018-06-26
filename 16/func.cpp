#include<iostream>
#include<functional>
struct test{
	void operator()(){
		std::cout<<"hw"<<std::endl;
	}

};
int main(){
	std::function<void()> f= test();
	f();
	test a;
	a();
	return 0;

}
