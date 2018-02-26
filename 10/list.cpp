#include"head.h"
int main(){
	list<string> arr;
	arr = myread("string.txt",arr,string(""));
	print(arr);
	arr.unique();
	print(arr);
	arr.sort();
	arr.unique();
	print(arr);
	arr.remove("qinhan");
	print(arr);
	auto cp = arr;
	arr.merge(cp);
	print(cp);
	print(arr);
	return 0;	

}
