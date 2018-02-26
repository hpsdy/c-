#include<iostream>
using namespace std;
int main(){
	const char arr[] = {'a','b','c','\0'};
	const char * ptr = arr;
	while(*ptr){
		cout<<*ptr<<endl;
		++ptr;
	}
	return 0;
}
