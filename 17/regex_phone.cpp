#include<iostream>
#include<cstdio>
#include<regex>
#include<string>
int main(){
	std::string pattern = "^\\(?\\d{3}\\)?((\\d[ .-]?){6})\\d$";
	std::string p;
	getline(std::cin,p);
	std::regex r(pattern);
	for (std::sregex_iterator it(p.begin(),p.end(),r),it_end; it!=it_end; ++it){
		printf("std:%s\n",it->str().c_str());
	}
	return 0;
}

