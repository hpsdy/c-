#include<iostream>

extern void print(); 
int b;
b=100;
int main(){
	extern int a;
	print();
	std::cout<<a<<std::endl;
	a=99;
	std::cout<<a<<std::endl;
	print();
	return 0;

}
