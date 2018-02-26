#include"strVec.h"
#include<iostream>
int main(){
	strVec arr;
	arr.push_back("a");
	arr.push_back("c");
	arr.push_back("d");
	arr.push_back("e");
	for(auto b=arr.begin(),e=arr.end();b!=e;++b){
		std::cout<<*b<<std::endl;
	}
	return 0;
}
