#include<cstdio>
#include<cstring>
#include<sstream>
#include<string>
#include<iostream>
#include<bitset>
int main(){
	int w = 100;
	std::cout<<std::hex<<std::endl;;
	std::cout<<w<<std::endl;
	std::cout<<std::oct<<std::endl;
	std::cout<<w<<std::endl;
	//std::cout<<std::bitset<<std::endl;
	//std::cout<<w<<std::endl;
	std::cout<<std::dec;
	std::bitset<20> xb(w);
	std::cout<<xb<<std::endl;
	long double x=321.3412321312;
	long double y=1.3412321312;
	std::cout<<y<<std::endl;
	printf("%13.5lf\n",x);
	int a=100;
	char b[20] = {'\0'};
	snprintf(b,sizeof(b),"%d",a);
	printf("%s:%d:%d\n",b,sizeof(b),strlen(b));
	std::string  s1 = "a100abc";
	std::stringstream io;
	io<<s1;
	int si;
	io>>si;
	printf("%d\n",si);
	return 0;
}
