#include<cmath>
#include<iomanip>
#include<iostream>

int main(){
	double x = 1234567.1234567;
	//std::cout<<std::fixed;
	std::cout<<std::hexfloat;
	std::cout<<x<<std::endl;
	std::cout.precision();
	double a = std::sqrt(2) * 10;
	std::cout<<a<<std::endl;
	std::cout.precision(10);
	std::cout<<a<<std::endl;
	std::cout<<x<<std::endl;
	return 0;

}
