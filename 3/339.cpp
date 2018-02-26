#include<iostream>
#include<cstring>
#include<string>
using namespace std;
int main(){
	char y[] = "abc";
	char *yp = y;
	cout<<static_cast<void*>(yp)<<endl;
	cout<<static_cast<void*>(&y[0])<<endl;
	cout<<&y<<endl;
	if(yp==&y[0]){
		cout<<"hxo"<<endl;
	}

	char x = 'a';
	char *xp = &x;
	cout<<"xp:"<<static_cast<void *>(xp)<<endl;
	string a = "123";
	const char *w = a.c_str();
	a = "abc";
	cout<<"xxxx"<<endl;
	cout<<"*w:"<<*w<<endl;
	cout<<"&w:"<<&w<<endl;
	cout<<"void*:"<<static_cast<const void*>(w)<<endl;
	cout<<"&a:"<<&a<<endl;
	cout<<"&a:"<<static_cast<void *>(&a)<<endl;
	cout<<"&a[0]:"<<static_cast<void*>(&a[0])<<endl;
	while(*w){
		cout<<*w<<endl;
		cout<<w<<endl;
		cout<<static_cast<const void*>(w)<<endl;
		w++;
	}
	return 0;
	char arr[5];
	cin>>arr;
	auto len = strlen(arr);
	cout<<"len:"<<len<<endl;
	char *p = arr;
	while(*p){
		cout<<*p<<endl;
		++p;
	}
	cout<<"++++"<<endl;
	cout<<arr[len]<<endl;
	cout<<sizeof(arr)<<endl;
	cout<<"++++"<<endl;
	for(auto c:arr){
		cout<<c<<endl;
	}
	return 1;
	char arr1[4]={'a','b','c','\0'},arr2[4]={'a','b','c','\0'};
//	cin>>arr1>>arr2;
	auto ret = strcmp(arr1,arr2);
	switch(ret){
		case 1:
			cout<<">"<<endl;
			break;
		case 0:
			cout<<"="<<endl;
			break;
		case -1:
			cout<<"<"<<endl;
			break;
		default:
			cout<<"unknow"<<endl;
			break;

	}
	cout<<arr1[2]<<endl;
	cout<<arr2[2]<<endl;
	cout<<arr1[3]<<endl;
	cout<<arr2[3]<<endl;
	return 0;
}
