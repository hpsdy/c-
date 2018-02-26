#include<locale>
#include"head.h"
int main(){
	locale::global(locale(""));
	wchar_t arr[] = L"秦瀚是帅哥";
	wcout<<arr[2]<<endl;
	return 0;

}

