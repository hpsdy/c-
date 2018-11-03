#include<cstdio>
#include<utility>
#include<iostream>
#include<string>
int main(){
	std::string a="10011111111111111110000";
	std::string b = std::move(a);
	std::cout<<(void*)&a<<std::endl;
	std::cout<<(void*)&b<<std::endl;
	std::string c="10011111111111111110000";
	std::string d = c;
	std::cout<<(void*)&c<<std::endl;
	std::cout<<(void*)&d<<std::endl;

	return 0;
}
