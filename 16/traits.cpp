#include<iostream>
#include<typeinfo>
template<typename T1,typename T2>
class test;/*{
public:
	test(T1 a,T2 b){
		printf("a:%s,b:%s\n",typeid(T1).name(),typeid(T2).name());
	}
};*/

template<typename T>
class test<const T*,int>{
public:
	test(T a){
		printf("b:%s\n",typeid(T).name());
	}
};
template<>
class test<int,int>{
public:
	test(int a){
		printf("int:%d\n",a);
	}
};

int rt(){
	return 123;
}
int main(){
	int m = 10;
//	test<char,char> a('a','b');
	test<const int*,int> b(m);
	test<int,int> c(99);
	rt();
}

