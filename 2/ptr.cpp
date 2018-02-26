#include<iostream>
#include<exception>
int main(){
	int init = 100;
	int *a = &init;
	int *e = &a;
	std::cout<<e<<" "<<*a<<" "<<init<<std::endl;
	*a = 99;
	std::cout<<a<<" "<<*a<<" "<<init<<std::endl;
	init = 88;
	std::cout<<a<<" "<<*a<<" "<<init<<std::endl;
	int b = 77;
	a = &b;
	std::cout<<a<<" "<<*a<<" "<<init<<std::endl;
	char x = ' ';
	if(x){
		std::cout<<"yes"<<std::endl;
	}else{
		std::cout<<"no"<<std::endl;
	}
	try{
		int *d;
		if(d){
			std::cout<<"no thing:"<<d<<" "<<*d<<std::endl;
		}
		throw "xxxyyyzzz";
	}catch(std::exception &e){
		std::cout<<"exception:"<<e.what()<<std::endl;
	}
	return 0;
}
