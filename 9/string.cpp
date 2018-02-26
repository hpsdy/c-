#include"head.h"
#include<locale>
int main(){
	locale::global(locale(""));
	wstring str=L"秦瀚你好";
	wcout<<str[0]<<endl;
	wcout<<str[1]<<endl;
	wcout<<str[2]<<endl;
	wcout<<str[3]<<endl;
	wcout<<"========"<<endl;
	const wchar_t *p = L"周末万岁";
	wcout<<"========"<<endl;
	const char *cp = "周末万岁";
	cout<<"cp:"<<cp<<endl;
	return 0;
//	wchar_t *p = arr;
	wstring wstr(p,3);
	string cstr(cp,3);
	wcout<<wstr<<endl;
	cout<<"========"<<endl;
	cout<<"cp:"<<cp<<endl;
	cout<<cstr<<endl;

	return 0;
}
