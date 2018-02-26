#include<iostream>
int main(){
	int a = 10;
	int &b = a;
	int &c = b;
	c = 99;
	std::cout<<a<<b<<c<<std::endl;
	return 0;
}
