#include"head.h"
#include<locale>
int main(){
	char as[] = "abcde";
	cout<<as[0]<<endl;
	cout<<*(as+2)<<endl;
	return 0;
//	wcout<<"========"<<endl;
//	const wchar_t *p = L"周末万岁";
//	wcout<<"========"<<endl;
	const char *cp = "周末万岁";
	string str(cp,3);
//	cout<<"cp:"<<cp<<endl;
	wcout<<L"abc"<<endl;
	wcout<<"1:"<<wcin.rdstate()<<endl;
	wcout.clear();
	cout.clear();
	cout<<"qinhan"<<endl;
	wcout<<"2:"<<wcin.rdstate()<<endl;
	wcout<<L"123"<<endl;
	wcout<<"cp:"<<cp<<endl;
//	wcout<<"cp:"<<str<<endl;
	wcout<<L"cba"<<endl;
	return 0;

	return 0;
}
