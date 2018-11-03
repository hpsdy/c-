//#include"class.cpp"
#include"class.h"
#include<cstdio>
//extern template class test<int>;
//template<typename T> class test;
template<>
class test<double>{
public:
	test(double a){
		printf("a:%09.2f\n",a);	
		printf("a:%f\n","1231231");	
	}
};
int main(){
	test<double> a(10.1);
	return 0;
}
