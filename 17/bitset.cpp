#include<bitset>
#include<cstdio>
#include<string>
#include<iostream>
int main(){
	std::string str;
	char x[20];
	std::cin>>str;
	std::cin>>x;
	std::cout<<str<<std::endl;
	std::cout<<x<<std::endl;
	std::cout<<sizeof(x)<<std::endl;
	std::bitset<32> a;
	std::cin>>a;
	std::cout<<a<<std::endl;
	return 0;
}
