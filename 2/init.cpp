#include<iostream>
#include<string>
using namespace std;
int main(){
	string a = "abc";
	int b = 10;
	bool c = true;
	//std::cout<<a+std::string(b)<<std::endl;
	string	x = to_string(b);	
	cout<<a+x<<endl;
	double y = 10.0/3.0;
	cout<<b.str()<<endl;
//	cout<<(a+static_case<string>(b))<<endl;
	/*int a=10.23;
	int e=a;
	std::cout<<a<<" "<<&a<<std::endl;
	std::cout<<e<<" "<<&e<<std::endl;
	const int  &b=a;
	std::cout<<b<<" "<<&b<<std::endl;
	const int *c = &a;
	double p = *c;
	std::cout<<p<<" "<<&p<<std::endl;
	std::cout<<c<<" "<<*c<<std::endl;
	a = 6.23;
	std::cout<<c<<" "<<*c<<std::endl;
	int a = 10.65;
	std::cout<<"a:"<<a<<" "<<&a<<std::endl;
	const int *const b = &a;
	std::cout<<"b:"<<b<<" "<<&b<<" "<<*b<<std::endl;
	const int *p = b;
	std::cout<<"p:"<<p<<" "<<&p<<" "<<*p<<std::endl;
	const int  &z = a;
	int w = z;
	std::cout<<"w:"<<w<<" "<<&w<<std::endl;
	a=1000;
	std::cout<<"b:"<<b<<" "<<&b<<" "<<*b<<std::endl;

	//int *x = b;
	//std::cout<<"x:"<<x<<" "<<&x<<" "<<*x<<std::endl;*/
	return 0;
}
