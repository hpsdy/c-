#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<bitset>
#include<typeinfo>
bool strTobinary(int str,char *desc){
	int *t = (int*)malloc(sizeof(str));
	std::cout<<"size:"<<sizeof(str)<<std::endl;
	*t = str;
	unsigned char *tmp = reinterpret_cast<unsigned char*>(t);
	std::bitset<20> b1(tmp[0]);
	std::bitset<20> b2(tmp[1]);
	std::cout<<"0:"<<int(tmp[0])<<std::endl;
	std::cout<<"1:"<<int(tmp[1])<<std::endl;
	std::cout<<"2:"<<int(tmp[2])<<std::endl;
	std::cout<<"3:"<<b1<<std::endl;
	std::cout<<"4:"<<b2<<std::endl;
	memcpy(desc,(char*)t,sizeof(str));
	free(t);
	return 0;
}
int main(){
	std::string xy="abc";
	char yx[] = "123";
	std::cout<<("123"+xy).c_str()<<std::endl;	
		
	char desc[10] = {'\0'};
	strTobinary(1000,desc);
	std::cout<<strlen(desc)<<std::endl;
	return 0;

}
