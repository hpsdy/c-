#include"class.h"
#include<cstdio>
extern template class test<int>;
int main(){
	test<int> a(10);
	return 0;
}
