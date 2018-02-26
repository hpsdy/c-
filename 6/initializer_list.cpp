#include<initializer_list>
//#include"head.h"
#include<iostream>
using namespace std;
void print(initializer_list<string> il){
	for(auto beg = il.begin();beg!=il.end();++beg){
		cout<<*beg<<endl;
	}
}
void test(int x);
void test(int y){
	cout<<y<<endl;
}
int main(){
	test(100);
	print({"123","abc","321","cba"});	
	//return EXIT_FAILURE;
	return EXIT_SUCCESS;
	return 0;
}
