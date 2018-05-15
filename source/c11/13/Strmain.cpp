#include "String.h"
#include <iostream>
int main(){
	String str1("abc");
	String str2("qinhan");
	String str3;
	str3 = str1+str2;
	std::cout<<str1<<std::endl;
	std::cout<<str2<<std::endl;
	std::cout<<str3<<std::endl;
	return 0;
	
}
