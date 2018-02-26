#include<iostream>
const int c = 100;
//int a = 10;
int main(){
	int a = 10;
	constexpr int b = c;
	std::cout<<b<<std::endl;
	const int &w = 10; 
	std::cout<<&100<<std::endl;
	return 0;
}
