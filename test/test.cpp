#include<iostream>
#include<string>
using namespace std;
#include"origin.cpp"
#include<stdarg.h>
#define debug(...) p(__VA_ARGS__)
void wr(int i,...){
	va_list args_ptr;
	va_start(args_ptr,i);
	int a = va_arg(args_ptr,int);
	cout<<a<<endl;
	va_end(args_ptr);
}
int main(){
	printf("qinhan");
	debug("ABC","CBAxxx");
	wr(100,99);
	return 0;

}
