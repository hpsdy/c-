#include<iostream>
#include<string>
#include<cstring>
#include<memory>
#include<typeinfo>
using namespace std;
template<typename T>
void destroy(T *t){
	t->~T();
	std::cout<<"type:"<<typeid(T).name()<<std::endl;
}
int main(){
	std::string q="asdasdasd";
	std::cout<<sizeof(q)<<std::endl;
	void *str = malloc(sizeof(std::string));
	std::string *str1 = (std::string*)str;
//	std::string *str = static_cast<std::string*>(str);
	std::string *xx = new(str) std::string("123");
	std::cout<<*(static_cast<std::string*>(str))<<std::endl;
	std::cout<<*xx<<std::endl;
	int *c = new int(10);
	//std::cout<<*(static_cast<std::string*>(c))<<std::endl;
	//std::cout<<*(std::string*)c<<std::endl;
//	xx->~string();
	destroy(xx);
//	delete xx;
	std::cout<<xx<<std::endl;
	std::cout<<*xx<<std::endl;
	xx = nullptr;
//	return 0;
	std::string a="abc";
	const char *b = a.c_str();
	std::cout<<"size:"<<a.size()<<std::endl;
	std::cout<<"size:"<<sizeof(a.c_str())<<std::endl;
	std::cout<<"size:"<<strlen(a.c_str())<<std::endl;
	std::string x="abc";
	if(x.empty()){
		std::cout<<"1"<<std::endl;
	}
	x="";
	if(x.empty()){
		std::cout<<"2"<<std::endl;
	}
	x="123";
	if(x.empty()){
		std::cout<<"3"<<std::endl;
	}
	x.clear();
	if(x.empty()){
		std::cout<<"4"<<std::endl;
	}
	return 0;
}
