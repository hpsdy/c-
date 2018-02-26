#include<iostream>
struct one{ 
	std::string bNo;
	int num=10;
	void getNum(){
		std::cout<<num<<std::endl;
	}
} oneObj;
int w;
double z;
int main(){
	std::cout<<"hello"<<std::endl;
	oneObj.getNum();
	int b;
	char c;
	std::cout<<b<<std::endl;
	std::cout<<c<<std::endl;
	std::cout<<w<<std::endl;
	std::cout<<z<<std::endl;
	return 0;
}
