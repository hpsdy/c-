#include<iostream>
#include<cstring>
int main(){
	char x[4] = "abc";
	std::cout<<x<<";size:"<<sizeof(x)<<";strlen:"<<strlen(x)<<std::endl;
	strcpy(x,"qinhan");
	std::cout<<x<<";size:"<<sizeof(x)<<";strlen:"<<strlen(x)<<std::endl;
	strcpy(x,"12");
	std::cout<<x<<";size:"<<sizeof(x)<<";strlen:"<<strlen(x)<<std::endl;
	return 0;
	
}
