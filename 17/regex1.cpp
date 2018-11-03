#include<regex>
#include<string>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<cstdio>
#include<locale>
int main(){
	//char a[] = "秦瀚";
//	std::locale lc("chs");
//	std::wcout.imbue(lc);
	std::setlocale(LC_ALL,"chs");
	wchar_t b[] = L"秦瀚";
	//std::cout<<sizeof(a)<<":"<<strlen(a)<<std::endl;
	std::cout<<sizeof(b)<<":"<<wcslen(b)<<std::endl;
	std::wcout<<L"这个"<<std::endl;
/*	for(int i=0;i<sizeof(b);++i){
		printf("%d:%x,size:%d\n",i,b[i],sizeof(b[i]));
	}*/
	return 0;
	std::string pattern("[^c]ei");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	std::regex r(pattern);
	std::string test_str = "hello freind receive";
	std::smatch results;
	if (std::regex_search(test_str,results,r)){
		std::cout<<results.str()<<std::endl;
	}
	try{
		std::regex rx("[[:alpha:]+\\.(cpp|cxx|cc)$",std::regex::icase);
	}catch(std::regex_error e){
		std::cout<<"what:"<<e.what()<<std::endl;
		std::cout<<"code:"<<e.code()<<std::endl;
	}
	return 0;
}
