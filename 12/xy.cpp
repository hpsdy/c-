#include<iostream>
#include<string>
#include<typeinfo>
#define log(a) printf("log %s",a)
#define log1(a) printf("log %s",#a)
#define log2(str,arg...) printf(str,##arg)
using namespace std;
#define base(fac) \
class fac##factory{ \
	public: \
		fac##factory(){std::cout<<typeid(*this).name()<<std::endl;} \
}; 
int  main(){
	log("abc");
	log1(a b c);
	log2("a %s %s","abc","cba");	
	cout<<endl;
	base(abc)
	abcfactory a;
	return 0;
}
